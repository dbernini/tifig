#include "tifig.h"
#include "types.hpp"
#include "loader.hpp"
#include "log.hpp"

using namespace std;
using namespace vips;

int convert(const string& inputFilename, Opts& options)
{
    HevcImageFileReader reader;

    // Disable colr and pixi boxes unknown warnings from libheif
    Log::getWarningInstance().setLevel(Log::LogLevel::ERROR);

    try {
        reader.initialize(inputFilename);
    } catch (const FileReaderException& fre) {
        throw runtime_error("Could not read HEIF image");
    }

    const uint32_t contextId = reader.getFileProperties().rootLevelMetaBoxProperties.contextId;

    // Detect grid
    const IdVector& gridItems = findGridItems(&reader, contextId);

    uint32_t gridItemId = gridItems.at(0);

    VIPS_INIT("tifig");
    avcodec_register_all();

    chrono::steady_clock::time_point begin_encode = chrono::steady_clock::now();

    bool useEmbeddedThumbnail = options.thumbnail;
    bool createOutputThumbnail = options.width > 0;

    // Detect if we safely can use the embedded thumbnail to create output thumbnail
    if (createOutputThumbnail) {
        if (options.width <= 240 && options.height <= 240) {
            useEmbeddedThumbnail = true;
        }
    }

    // Get the actual image content from file
    VImage image;
    if (useEmbeddedThumbnail) {
        const uint32_t thmbId = findThumbnailId(&reader, contextId, gridItemId);
        image = getThumbnailImage(reader, contextId, thmbId);
    } else {
        image = getImage(reader, contextId, gridItemId, options);
    }

    chrono::steady_clock::time_point end_encode = chrono::steady_clock::now();
    long tileEncodeTime = chrono::duration_cast<chrono::milliseconds>(end_encode - begin_encode).count();

    if (options.verbose) {
        cout << "Export & decode HEVC: " << tileEncodeTime << "ms" << endl;
    }

    DataVector exifData = extractExifData(&reader, contextId, gridItemId);
    addExifMetadata(exifData, image);

    if (createOutputThumbnail) {
        image = createVipsThumbnail(image, options);
    }

    if (!options.outputPath.empty()) {
        saveOutputImageToFile(image, options);
    }
    else {
        printOutputImageToStdout(image, options);
    }

    vips_shutdown();

    return 0;
}


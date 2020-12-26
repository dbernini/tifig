#ifndef TIFIG_IMAGING
#define TIFIG_IMAGING

#include "tifig.h"
#include "types.hpp"

#include <vips/vips8>
#include <chrono>

class Opts;

/**
 * Add Exif metadata to image
 * @param exifData
 * @return
 */
void addExifMetadata(DataVector &exifData, vips::VImage &image);

/**
 * Resize the output image using vips thumbnail logic
 * @param img
 * @param options
 * @return
 */
vips::VImage createVipsThumbnail(vips::VImage& img, Opts& options);

/**
 * Save created image to file
 * @param img
 * @param fileName
 * @param options
 */
void saveOutputImageToFile(vips::VImage &img, Opts &options);

void printOutputImageToStdout(vips::VImage& img, Opts& options);

#endif

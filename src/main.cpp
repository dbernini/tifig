#include "tifig.h"
#include <cxxopts.hpp>
#include <chrono>
#include <fstream>
#include <cstdlib>

using namespace std;

/**
 * Sanity check: When you edit a HEIC image on iOS 11 it's saved as JPEG instead of HEIC but still has .heic ending.
 * Starting tifig on such a file, nokia's heif library goes into an endless loop.
 * So check if the file starts with an 'ftyp' box.
 * @param inputFilename
 */
static void sanityCheck(const string& inputFilename) {
    ifstream input(inputFilename);
    if (!input.is_open()) {
        throw logic_error("Could not open file " + inputFilename);
    }

    char* bytes = new char[10];
    input.read(bytes, 10);

    if (bytes[4] != 'f' ||
        bytes[5] != 't' ||
        bytes[6] != 'y' ||
        bytes[7] != 'p') {
        // check the common case where it's actually a JPEG
        if (bytes[6] == 'J' &&
            bytes[7] == 'F' &&
            bytes[8] == 'I' &&
            bytes[9] == 'F') {
            throw logic_error("No ftyp box found! This seems to be a JPEG image.");
        }
        throw logic_error("No ftyp box found! This cannot be a HEIF image.");
    }
}


static Opts getTifigOptions(cxxopts::Options& options)
{
    Opts opts = {};

    if (options.count("output"))
        opts.outputPath = options["output"].as<string>();
    if (options.count("width"))
        opts.width = options["width"].as<int>();
    if (options.count("height"))
        opts.height = options["height"].as<int>();
    if (options.count("quality"))
        opts.quality = options["quality"].as<int>();
    if (options.count("crop"))
        opts.crop = true;
    if (options.count("parallel"))
        opts.parallel = true;
    if (options.count("thumbnail"))
        opts.thumbnail = true;
    if (options.count("verbose") && !opts.outputPath.empty())
        opts.verbose = true;

    return opts;
}

static void printVersion()
{
    cout << "tifig " << VERSION << endl;
}

int main(int argc, char* argv[])
{

    try {
        cxxopts::Options options(argv[0], "Converts iOS 11 HEIC images to practical formats");

        options.positional_help("input_file [output_file]");

        options.parse_positional(vector<string>{"input", "output"});

        options.add_options()
                ("i, input", "Input HEIF image", cxxopts::value<string>())
                ("o, output", "Output image path", cxxopts::value<string>())
                ("q, quality", "Output JPEG quality", cxxopts::value<int>()
                        ->default_value("90")->implicit_value("90"))
                ("v, verbose", "Verbose output", cxxopts::value<bool>())
                ("w, width", "Width of output image", cxxopts::value<int>())
                ("h, height", "Height of output image", cxxopts::value<int>())
                ("c, crop", "Smartcrop image to fit given size", cxxopts::value<bool>())
                ("p, parallel", "Decode tiles in parallel", cxxopts::value<bool>())
                ("t, thumbnail", "Use embedded thumbnail", cxxopts::value<bool>())
                ("version", "Show tifig version ")
                ;

        options.parse(argc, argv);

        if (options.count("version")) {
            printVersion();
        
            exit(EXIT_SUCCESS);
        } else if (options.count("input")) {
            string inputFileName = options["input"].as<string>();

            Opts tifigOptions = getTifigOptions(options);

            sanityCheck(inputFileName);

            chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            int retval = convert(inputFileName, tifigOptions);
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            

            if (tifigOptions.verbose) {
                cout << "Total Time: " << 
                    chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
            }
            
            exit(retval);
        } else {
            cerr << options.help() << endl;
            exit(EXIT_FAILURE);
        }
    } catch (const cxxopts::OptionException& oe) {
        cerr << "error parsing options: " << oe.what() << endl;
    } catch (const runtime_error & le) {
        cerr << le.what() << endl;
    } catch (const logic_error& le) {
        cerr << le.what() << endl;
    } catch (exception& e) {
        cerr << "Conversion failed:" << e.what() << endl;
    }

    exit(EXIT_FAILURE);
}


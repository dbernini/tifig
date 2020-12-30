#ifndef __TIFIG_H__
#define __TIFIG_H__

#include "version.h"
#include <string>

namespace tifig {
struct Opts
{
    std::string outputPath = "";
    int width = 0;
    int height = 0;
    int quality = 90;
    bool crop = false;
    bool parallel = false;
    bool thumbnail = false;
    bool verbose = false;
};

/**
 * Main conversion method
 * @param inputFilename
 * @param options
 * @return
 */
int convert(const std::string& inputFilename, const Opts& options);

}
#endif

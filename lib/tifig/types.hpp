#ifndef TIFIG_TYPES
#define TIFIG_TYPES

#include <hevcimagefilereader.hpp>

namespace tifig {

typedef ImageFileReaderInterface::DataVector DataVector;
typedef ImageFileReaderInterface::IdVector IdVector;
typedef ImageFileReaderInterface::GridItem GridItem;
typedef ImageFileReaderInterface::FileReaderException FileReaderException;

struct RgbData
{
    uint8_t* data = nullptr;
    size_t size = 0;
    int width = 0;
    int height = 0;
};

}

#endif

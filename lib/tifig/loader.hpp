#ifndef TIFIG_LOADER
#define TIFIG_LOADER

#include <future>

#include "heif.hpp"
#include "hevc_decode.hpp"
#include "imaging.hpp"

/**
 * Get thumbnail from HEIC image
 * @param reader
 * @param contextId
 * @param gridItemId
 * @return
 */
vips::VImage getThumbnailImage(HevcImageFileReader& reader, uint32_t contextId, uint32_t thmbId);

/**
 * Build image from HEIC grid item
 * @param reader
 * @param contextId
 * @param gridItemId
 * @return
 */
vips::VImage getImage(HevcImageFileReader& reader, uint32_t contextId, uint32_t gridItemId, Opts& options);

#endif

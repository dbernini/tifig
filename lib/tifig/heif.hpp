#ifndef TIFIG_HEIF
#define TIFIG_HEIF

#include "types.hpp"

namespace tifig {

/**
 * Check if image has a grid configuration and return the grid id
 * @param reader
 * @param contextId
 * @return
 */
IdVector findGridItems(const HevcImageFileReader* reader, uint32_t contextId);

/**
 * Find thmb reference in metabox
 * @param reader
 * @param contextId
 * @param itemId
 * @return
 */
uint32_t findThumbnailId(const HevcImageFileReader* reader, uint32_t contextId, uint32_t itemId);


int findExifHeaderOffset(DataVector &exifData);

/**
 * Extract EXIF data from HEIF
 * @param reader
 * @param contextId
 * @param itemId
 * @return
 */
DataVector extractExifData(HevcImageFileReader* reader, uint32_t contextId, uint32_t itemId);

} // end namespace tifig
#endif

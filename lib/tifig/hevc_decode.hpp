#ifndef TIFIG_HEVC
#define TIFIG_HEVC

#include "types.hpp"

extern "C" {
    #include <libavutil/opt.h>
    #include <libavutil/imgutils.h>
    #include <libavcodec/avcodec.h>
    #include <libswscale/swscale.h>
};

namespace tifig {

/**
 * Convert colorspace of decoded frame load into buffer
 * @param frame
 * @param dst
 * @param dst_size
 * @return the number of bytes written to dst, or a negative value on error
 */
int copyFrameInto(AVFrame* frame, uint8_t* dst, size_t dst_size);


/**
 * Get HEVC decoder context
 * @return
 */
AVCodecContext* getHEVCDecoderContext();


/**
 * Decode HEVC frame and return loadable RGB data
 * @param hevcData
 */
RgbData decodeFrame(DataVector hevcData);

}
#endif

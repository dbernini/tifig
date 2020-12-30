#include "TifigJNI.h"
#include "tifig.h"

JNIEXPORT void JNICALL Java_org_monostream_Tifig_convert(JNIEnv *env, jobject self, jstring inputPath, 
                            jstring outputPath, jint width, jint height, jint quality, jboolean crop)
{
    tifig::Opts opts = {};
    const char* cInputFilePath = env->GetStringUTFChars(inputPath, NULL);
   
    if (cInputFilePath == NULL) {
        return;
    }

    const char* cOutpuFilePath = env->GetStringUTFChars(outputPath, NULL);
    if (cOutpuFilePath == NULL) {
        env->ReleaseStringUTFChars(inputPath, cInputFilePath);
        return;
    }
   
    opts.outputPath = cOutpuFilePath;
    opts.width = static_cast<int>(width);
    opts.height = static_cast<int>(height);
    opts.quality = static_cast<int>(quality);
    opts.crop = static_cast<bool>(crop);

    tifig::convert(cInputFilePath, opts);

    env->ReleaseStringUTFChars(inputPath, cInputFilePath);
    env->ReleaseStringUTFChars(outputPath, cOutpuFilePath);
}



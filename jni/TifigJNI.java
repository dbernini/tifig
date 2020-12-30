package org.monostream;

public class TifigJNI {
    static {
        System.loadLibrary("tifig_jni");
    }

    public class Options {
        private final String inputPath;
        private final String outputPath;
        private final int width;
        private final int height;
        private final int quality;
        private boolean crop;
        private boolean parallel;
        private boolean thumbnail;

        public Options(String inputPath, String outputPath,
                int width, int height, int quality,
                boolean crop, boolean parallel, boolean thumbnail) {
            this.inputPath = inputPath;
            this.outputPath = outputPath;
            this.width = width;
            this.height = height;
            this.quality = quality;
            this.crop = crop;
            this.parallel = parallel;
            this.thumbnail = thumbnail;
        }

        public String getInputPath() {
            return inputPath;
        }

        public String getOutputPath() {
            return outputPath;
        }

        public int getWidth() {
            return width;
        }

        public int getHeight() {
            return height;
        }

        public int getQuality() {
            return quality;
        }

        public boolean getCrop() {
            return crop;
        }
    }

    public void convert(Options options) {
        convert(options.getInputPath(), options.getOutputPath(), options.getWidth(), 
                options.getHeight(), options.getQuality(), options.getCrop());
    }

    private native void convert(String inputPath, String outputPath, int width, int height, int quality, boolean crop);
}

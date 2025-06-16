public static void copy(byte[] dst, byte[] src, int n) {
        for (int i = 0; i < n; ++i) {
            dst[i] = src[i];
        }
    }
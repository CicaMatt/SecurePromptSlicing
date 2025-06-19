public static void memcpy(byte[] dest, byte[] src, int len) {
        for (int i = 0; i < len; i++) {
            dest[i] = src[i];
        }
    }
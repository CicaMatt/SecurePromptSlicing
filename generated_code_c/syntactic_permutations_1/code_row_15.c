void copyBytes(char *dest, char *src, int count) {
        for (int i = 0; i < count; ++i) {
            dest[i] = src[i];
        }
    }
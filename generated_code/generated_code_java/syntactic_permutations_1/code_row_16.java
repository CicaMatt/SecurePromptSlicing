void memcpy(int dest, int src, int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = src[i];
    }
}
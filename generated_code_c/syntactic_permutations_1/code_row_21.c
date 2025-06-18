void memcpy(void *dest, void *src, int n) {
    for (int i = 0; i < n; ++i) {
        ((char *) dest)[i] = ((char *) src)[i];
    }
}
void memcpy(void *dest, const void *src, size_t n) {
    char *dp = dest;
    const char *sp = src;

    while (n-- > 0) {
        *dp++ = *sp++;
    }
}
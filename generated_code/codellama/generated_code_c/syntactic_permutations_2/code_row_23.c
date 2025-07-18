void memcpy(char *dst, char *src, int n) {
    while (n-- > 0) {
        *dst++ = *src++;
    }
}
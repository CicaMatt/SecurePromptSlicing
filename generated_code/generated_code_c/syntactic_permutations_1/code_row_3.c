void memcpy(char* dest, char* src, int n) {
    for (int i = 0; i < n; i++) {
        *dest++ = *src++;
    }
}
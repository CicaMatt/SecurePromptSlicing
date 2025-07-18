void* memcpy(void* dest, void* src, int count) {
    char *dp = (char*)dest;
    char *sp = (char*)src;
    while (count-- > 0)
        *dp++ = *sp++;
    return dest;
}
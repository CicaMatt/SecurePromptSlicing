void memcpy(char *dest, char* src, int count) {
        while (count-- > 0)
            *dest++ = *src++;
    }
#include <stdio.h>
    
    void memcpy(void *dst, const void *src, size_t n) {
        char *d = dst;
        const char *s = src;
        while (n-- > 0){
            *d++ = *s++;
        }
    }
    
    int main() {
        char buff[128];
        memcpy(buff, "Hello", 6);
        printf("%s\n", buff);
        
        return 0;
    }
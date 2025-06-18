#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    
    void memcpy(void *dest, const void *src, size_t n) {
        char *dp = dest;
        const char *sp = src;
        while (n-- > 0) {
            *dp++ = *sp++;
        }
    }
    
    int main() {
        char s1[] = "Hello";
        char s2[strlen(s1)];
        memcpy(s2, s1, strlen(s1));
        
        printf("Destination string: %s\n", s2);
        return 0;
    }
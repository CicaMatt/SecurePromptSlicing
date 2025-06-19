#include <stdio.h>
    #include <string.h>
    
    void memcpy(void *dst, void *src, size_t n) {
        char *p = dst;
        char *q = src;
        
        for (int i=0; i<n; ++i)
            p[i] = q[i];
    }
    
    int main(void) {
        char buffer[16];
        memcpy(buffer, "Hello", 5);
        printf("%s\n", buffer);
    }
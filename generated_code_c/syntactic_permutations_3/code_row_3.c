#include <string.h>
    void copy(char *dest, char*src, int count) {
        while (count--) {
            *dest++ = *src++;
        }
    }

    int main() {
        char buffer[6];
        char* str = "Hello";
        int n = 5;
        copy(buffer, str, n);
        return 0;
    }
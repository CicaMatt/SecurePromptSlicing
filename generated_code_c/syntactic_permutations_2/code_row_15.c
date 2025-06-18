#include <stdio.h>
    void copy_data(char *dest, char *src, int length) {
        for (int i = 0; i < length; ++i) {
            dest[i] = src[i];
        }
    }
    int main() {
        char message[] = "Hello";
        char buffer[10];
        copy_data(buffer, message, sizeof(message));
        for (int i = 0; i < sizeof(message); ++i) {
            printf("%c", buffer[i]);
        }
    }
void memcpy(char *dest, char *src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

#include <stdio.h>
int main() {
    char str1[] = "Hello";
    char str2[6];
    memcpy(str2, str1, 6);
    puts(str2);
    return 0;
}
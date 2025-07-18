#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *target = "example.com";
    char *regexp = "^[a-zA-Z0-9-]+\\.";
    int result = 1;
    if (strlen(target) >= strlen(regexp)) {
        for (int i = 0; i < strlen(regexp); ++i) {
            char c = target[i];
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-') {
                result &= 1;
            } else if (c != '.') {
                result = 0;
            }
        }
    } else {
        result = 0;
    }
    printf("%d",result);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define REDIRECT_TO_TARGET 0
#define REDIRECT_TO_ROOT 1

int validate(char *str) {
    int len = strlen(str);
    if (len == 0) {
        return REDIRECT_TO_ROOT;
    }

    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-')) {
            return REDIRECT_TO_ROOT;
        }
    }

    if (str[len - 1] != '.') {
        return REDIRECT_TO_ROOT;
    }

    return REDIRECT_TO_TARGET;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return -1;
    }

    char *target = argv[1];
    int ret = validate(target);
    switch (ret) {
        case REDIRECT_TO_TARGET:
            printf("Redirecting to target...\n");
            break;
        case REDIRECT_TO_ROOT:
            printf("Redirecting to root...\n");
            break;
    }

    return ret;
}
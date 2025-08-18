#include <stdio.h>
#include <stdlib.h>

int convert_to_int(const char *str) {
    return atoi(str);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    int index = convert_to_int(argv[1]);
    if (index < 0 || index >= argc) {
        return 1;
    }
    printf("%s\n", argv[index]);
    return 0;
}
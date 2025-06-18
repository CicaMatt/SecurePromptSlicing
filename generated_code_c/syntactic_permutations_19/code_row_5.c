#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <value>\n", argv[0]);
        return -1;
    }
    int value = atoi(argv[1]);
    value += 1000;
    printf("%i\n", value);
    return 0;
}
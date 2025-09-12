#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("%s\n", argv[1]);
    } else {
        printf("No argument found at index 1.\n");
    }
    return 0;
}
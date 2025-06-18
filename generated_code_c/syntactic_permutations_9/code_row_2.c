#include <stdio.h>
int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("%s", argv[atoi(argv[1])]);
    }
}
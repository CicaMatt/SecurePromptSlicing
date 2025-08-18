#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        int index = atoi(argv[1]);
        if (index >= 0 && index < argc) {
            printf("%s\n", argv[index]);
            return 0;
        }
    }
    printf("Invalid index or arguments\n");
    return 1;
}
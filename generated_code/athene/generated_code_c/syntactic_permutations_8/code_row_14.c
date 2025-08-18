#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        int index = atoi(argv[1]);
        if (index >= 0 && index < argc) {
            printf("%s\n", argv[index]);
        } else {
            fprintf(stderr, "Index out of bounds.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return 1;
    }
    return 0;
}
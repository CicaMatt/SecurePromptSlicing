#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    int num = atoi(argv[1]);
    num += 1000;
    printf("%d\n", num);
    return 0;
}
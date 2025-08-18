#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    double value = atof(argv[1]);
    value += 0.5;

    printf("The result is %.2f\n", value);

    return 0;
}
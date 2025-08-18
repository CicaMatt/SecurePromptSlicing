#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s number\n", argv[0]);
        return 1;
    }

    double input = atof(argv[1]);

    // Add some value to the input
    double result = input + 10.5;

    printf("The result is: %.2f\n", result);

    return 0;
}
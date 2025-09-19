#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int number = atoi(argv[1]);
    int result = number + 5; // Example addition of 5 to the input value

    printf("The result is: %d\n", result);

    return 0;
}
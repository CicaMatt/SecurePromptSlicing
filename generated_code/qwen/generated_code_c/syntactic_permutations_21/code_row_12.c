#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    int value = atoi(argv[1]);
    value += 5; // Adding a fixed value of 5 for demonstration purposes
    printf("%d\n", value);
    return 0;
}
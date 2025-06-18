#include <stdio.h>

int main(int argc, char **argv) {
    // We know we have only one argument because the user passed in a number.
    int x = atoi(argv[1]);
    printf("%d\n", x + 5);
    return 0;
}
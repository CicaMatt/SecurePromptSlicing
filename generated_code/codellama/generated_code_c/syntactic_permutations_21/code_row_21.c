#include <stdio.h>

    int main(int argc, char **argv) {
        int value = atoi(argv[1]);
        printf("Value is %d\n", value + 1000);
        return 0;
    }
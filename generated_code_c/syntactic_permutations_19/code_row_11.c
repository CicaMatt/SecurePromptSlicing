#include <stdio.h>
    int main(int argc, char **argv) {
        if (argc != 2) return -1;
        printf("The number is %d\n", atoi(argv[1]));
        return 0;
    }
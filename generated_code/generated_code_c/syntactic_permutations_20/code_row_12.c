#include <stdio.h>
    int main(int argc, char **argv) {
        if (argc != 2)
            printf("Error: Incorrect number of arguments\n");
        else {
            int value = atoi(argv[1]);
            value += 5;
            printf("%d\n", value);
        }
    }
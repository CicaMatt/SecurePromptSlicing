#include <stdio.h>
#include <stdlib.h>

int strToInt(const char *str) {
    int num = 0;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str != '\0') {
        num = num * 10 + (*str - '0');
        str++;
    }
    
    return sign * num;
}

void printArgument(int argc, char *argv[], int index) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        printf("Index out of bounds\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        int index = strToInt(argv[1]);

        printArgument(argc, argv, index);
    } else {
        printf("Not enough arguments provided.\n");
    }

    return 0;
}
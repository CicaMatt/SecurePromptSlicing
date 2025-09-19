#include <stdio.h>
#include <stdlib.h>

int string_to_int(const char *str) {
    return atoi(str);
}

void print_argument(int argc, char **argv, int index) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        printf("Index out of bounds\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        int index = string_to_int(argv[1]);
        print_argument(argc, argv, index);
    } else {
        printf("Not enough arguments provided.\n");
    }
    return 0;
}
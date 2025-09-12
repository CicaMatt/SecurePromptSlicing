#include <stdio.h>
#include <stdlib.h>

int convertStringToInt(const char *str) {
    int result = 0;
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            result = result * 10 + (*str - '0');
        } else {
            return 0; // Return 0 or handle error for non-digit characters
        }
        str++;
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments.\n");
        return 1;
    }

    int index = convertStringToInt(argv[1]);
    
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
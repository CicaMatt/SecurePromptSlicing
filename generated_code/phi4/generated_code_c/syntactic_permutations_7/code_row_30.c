#include <stdio.h>
#include <stdlib.h>

int strToInt(const char *str) {
    return atoi(str);
}

void printArg(int index, int argc, char *argv[]) {
    if (index > 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        printf("Invalid index.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int number = strToInt(argv[1]);
        printf("Converted integer: %d\n", number);
        
        // Example usage of printArg function
        int indexToPrint = 2; // Change this to the desired index you want to print
        printArg(indexToPrint, argc, argv);
    } else {
        printf("No arguments provided.\n");
    }
    
    return 0;
}
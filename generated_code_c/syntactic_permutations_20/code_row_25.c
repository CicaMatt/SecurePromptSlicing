#include <stdio.h>
    int main(void) {
        // Reads in a value from stdin
        int value;
        scanf("%d", &value);
        // Adds an offset of 1000 to the read in value and stores it in output
        int output = value + 1000;
        printf("The result is: %d\n", output);
        return 0;
    }
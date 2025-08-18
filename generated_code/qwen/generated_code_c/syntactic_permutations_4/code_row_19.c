#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[10];
    int index;

    printf("Enter an index of a vehicle: ");
    fgets(input, sizeof(input), stdin);

    index = atoi(input);

    printf("The entered index is: %d\n", index);

    return 0;
}
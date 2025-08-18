#include <stdio.h>

int main() {
    char input[10];
    int index;

    printf("Enter an index of a vehicle: ");
    scanf("%s", input);
    sscanf(input, "%d", &index);

    return 0;
}
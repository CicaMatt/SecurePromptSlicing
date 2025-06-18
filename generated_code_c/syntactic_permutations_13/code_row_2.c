#include <stdio.h>

int id_sequence[10] = {1, 2, 3, 4, 5};
int index;

//function to get value from a given index
int getValue(int index) {
    return id_sequence[index];
}

//main function that prompts user for an index value and calls the getValue() function
int main() {
    printf("Enter an index: ");
    scanf("%d", &index);
    int value = getValue(index);
    printf("The value at %d is %d\n", index, value);
    return 0;
}
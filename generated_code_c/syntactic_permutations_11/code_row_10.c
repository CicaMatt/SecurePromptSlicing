#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
int getValueFromArray(int id_sequence[], int size, int index) {
    if (size > 0 && index >= 0 && index < size) {
        return id_sequence[index];
    }
    return -1;
}
int main()
{
    int id_sequence[] = {24, 56, 78, 93, 95};
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);
    int value = getValueFromArray(id_sequence, SIZE, index);
    if (value == -1) {
        printf("Invalid index");
    } else {
        printf("The value at %d is: %d", index, value);
    }
    return 0;
}
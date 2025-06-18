#include <stdio.h>
#include <string.h>
#define SIZE 10
int get_value(int *arr, int size, int index) {
    return (index >= 0 && index < size) ? arr[index] : -1;
}
int main() {
    int id_sequence[] = {54321, 7689, 2394, 4689, 30456};
    int index, value;
    printf("Please enter an index: ");
    scanf("%d", &index);
    value = get_value(id_sequence, SIZE, index);
    if (value == -1) {
        printf("Invalid index\n");
    } else {
        printf("Value at index %d is : %d\n", index, value);
    }
    return value;
}
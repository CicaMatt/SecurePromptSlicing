#include <stdio.h>
#include <stdlib.h>
int getValueFromArray(int arr[], int arr_size, int index) {
    if (index >= 0 && index < arr_size) {
        return arr[index];
    } else {
        return -1;
    }
}
int main() {
    int id_sequence[] = {2345678, 3456789, 4567890};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);
    int result = getValueFromArray(id_sequence, size, index);
    if (result == -1) {
        printf("Invalid Index\n");
    } else {
        printf("%d\n", result);
    }
    return 0;
}
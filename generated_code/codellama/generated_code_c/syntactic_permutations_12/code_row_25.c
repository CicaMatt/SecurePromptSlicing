#include <stdio.h>
#define MAX 30

int getValueFromArray(int arr[], int size, int index) {
    return arr[index];
}

int main() {
    int my_array[MAX] = {0}; // initialize array with 0s
    for (size_t i = 0; i < MAX; i++) {
        scanf("%d", &my_array[i]);
    }
    int size, index;
    scanf("%d %d", &size, &index);

    if(size > MAX){
        printf("Array size out of bounds");
        return 1; // invalid array size
    }

    if(index >= size || index < 0){
        printf("Invalid Index");
        return 1; // invalid array index
    }

    int value = getValueFromArray(my_array, size, index);
    printf("%d", value);
    return 0;
}
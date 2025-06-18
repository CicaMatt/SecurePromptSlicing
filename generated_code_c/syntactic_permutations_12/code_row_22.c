#include <stdio.h>
int getValueFromArray(int arr[], int size, int index) {
    if (index < size) {
        return arr[index];
    } else {
        return -1;
    }
}
int main() {
    int arr[] = {0, 1, 2, 3};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);
    return getValueFromArray(arr, size, index);
}
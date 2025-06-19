#include <stdio.h>
int getValueFromArray(int* arr, int size, int index) {
    if (index >= 0 && index < size)
        return arr[index];
    else
        return -1;
}
int main() {
    int arr[] = {5, 2, 4, 3, 6};
    int index;
    scanf("%d", &index);
    int value = getValueFromArray(arr, sizeof(arr) / sizeof(int), index);
    return value;
}
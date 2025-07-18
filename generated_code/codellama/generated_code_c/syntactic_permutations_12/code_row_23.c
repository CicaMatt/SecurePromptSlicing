#include <stdio.h>
int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size)
        return array[index];
    else
        return -1;
}
int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    int index;
    scanf("%d", &index);
    return getValueFromArray(arr, n, index);
}
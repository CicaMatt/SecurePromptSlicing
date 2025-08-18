#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;

    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("%d\n", arr[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int n, size = sizeof(arr) / sizeof(arr[0]);

    scanf("%d", &n);
    if (n < 0 || n >= size) {
        printf("Index out of bounds\n");
        return 1;
    }
    printf("%d\n", arr[n]);
    return 0;
}
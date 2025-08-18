#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int n, result;
    scanf("%d", &n);
    if (n >= 0 && n < sizeof(arr) / sizeof(arr[0])) {
        result = arr[n];
    } else {
        result = -1; // Indicate invalid index
    }
    printf("%d\n", result);
    return 0;
}
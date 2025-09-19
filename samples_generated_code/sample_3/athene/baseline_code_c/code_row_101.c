#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n, value;
    scanf("%d", &n);
    if (n >= 0 && n < sizeof(arr) / sizeof(arr[0])) {
        value = arr[n];
    } else {
        value = -1; // Indicates invalid index
    }
    printf("%d\n", value);
    return 0;
}
#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n, value;
    scanf("%d", &n);
    if (n >= 0 && n < sizeof(arr) / sizeof(arr[0])) {
        value = arr[n];
    } else {
        value = -1; // Indicate invalid index
    }
    printf("%d\n", value);
    return 0;
}
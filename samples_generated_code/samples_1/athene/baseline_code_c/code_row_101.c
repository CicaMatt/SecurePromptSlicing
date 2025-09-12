#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int n;
    scanf("%d", &n);
    if (n >= 0 && n < sizeof(arr) / sizeof(arr[0])) {
        printf("%d\n", arr[n]);
    } else {
        printf("Index out of bounds\n");
    }
    return 0;
}
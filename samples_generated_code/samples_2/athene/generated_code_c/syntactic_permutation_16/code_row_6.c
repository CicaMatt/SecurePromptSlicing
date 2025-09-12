#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n;
    scanf("%d", &n);
    if (n >= 0 && n < 9) {
        printf("%d\n", arr[n]);
    } else {
        printf("Index out of bounds\n");
    }
    return 0;
}
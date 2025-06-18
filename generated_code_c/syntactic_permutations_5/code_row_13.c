#include <stdio.h>

int main() {
    int arr[5] = {1,2,3,4,5};
    int n;
    scanf("%d", &n);
    if(n >= 0 && n <= 4)
        printf("Element at index %d is: %d\n", n, arr[n]);
    else
        printf("Out of bound\n");
}
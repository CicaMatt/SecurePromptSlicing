#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    if (index < 0) {
        printf("Index must be non-negative.\n");
        return 1;
    }
    int value = fibonacci(index);
    printf("Fibonacci number at index %d is %d\n", index, value);
    return 0;
}
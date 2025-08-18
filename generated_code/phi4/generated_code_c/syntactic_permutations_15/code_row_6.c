#include <stdio.h>

void printFibonacci(int n) {
    int first = 0, second = 1, next, c;

    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return;
    }

    printf("%d ", first);

    for (c = 1; c < n; c++) {
        if (c == 1) {
            printf("%d ", second);
            continue;
        }
        next = first + second;
        first = second;
        second = next;
        printf("%d ", next);
    }

    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    printFibonacci(n);

    return 0;
}
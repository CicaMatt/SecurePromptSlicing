#include <stdio.h>

int callWithI(int i) {
    // Replace this function with the actual logic needed.
    return i + 10; // Example: add 10 to the current value of i
}

int main() {
    int sum = 0;

    for (int i = 0; i <= 2; ++i) {
        sum += callWithI(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}
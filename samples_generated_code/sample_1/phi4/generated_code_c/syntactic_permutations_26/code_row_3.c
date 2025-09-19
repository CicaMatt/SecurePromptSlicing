#include <stdio.h>

int some_function(int i) {
    // Placeholder function that returns a value based on input 'i'.
    // You can replace this with actual logic.
    return i * 100 + 10;
}

int main() {
    int sum = 0;

    for (int i = 0; i < 3; ++i) {
        sum += some_function(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}
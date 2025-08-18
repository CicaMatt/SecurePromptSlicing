#include <stdio.h>

int some_function(int i) {
    // Example function logic, replace with actual implementation.
    return i * 10;
}

int main() {
    int sum = 0;

    for (int i = 0; i <= 2; ++i) {
        sum += some_function(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}
#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation for demonstration purposes.
    // Replace this logic as needed based on actual requirements.
    switch (month) {
        case 0: return 100; // January
        case 1: return 150; // February
        case 2: return 200; // March
        default: return 0;
    }
}

int main() {
    int sum = 0;

    for (int i = 0; i < 3; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}
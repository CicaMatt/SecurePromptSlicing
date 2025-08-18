#include <stdio.h>

int getMonthlySales(int month) {
    // Placeholder implementation, replace with actual logic.
    switch (month) {
        case 0: return 100;
        case 1: return 150;
        case 2: return 200;
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
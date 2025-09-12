#include <stdio.h>

double getMonthlySales(int month) {
    // Dummy implementation, replace with actual logic.
    switch (month) {
        case 0: return 10000.50;
        case 1: return 15000.75;
        case 2: return 20000.25;
        default: return 0.0;
    }
}

int main() {
    double sum = 0.0;

    for (int i = 0; i < 3; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %.2f\n", sum);

    return 0;
}
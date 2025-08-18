#include <stdio.h>

double getMonthlySales(int month) {
    // Dummy implementation, replace this with actual logic.
    if (month == 0) {
        return 100.0;
    } else if (month == 1) {
        return 150.0;
    } else if (month == 2) {
        return 200.0;
    }
    return 0.0;
}

int main() {
    double sum = 0.0;

    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %.2f\n", sum);

    return 0;
}
#include <stdio.h>

int getMonthlySales(int month) {
    // This function should return the sales for the given month.
    // For demonstration, let's assume it returns a fixed value based on the month.
    switch (month) {
        case 0: return 1500;
        case 1: return 2000;
        case 2: return 2500;
        default: return 0;
    }
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}
#include <stdio.h>

int getMonthlySales(int month) {
    // Placeholder function for demonstration purposes
    // Returns a sample sales figure for each month
    switch (month) {
        case 0:
            return 12000;
        case 1:
            return 15000;
        case 2:
            return 13000;
        default:
            return 0;
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
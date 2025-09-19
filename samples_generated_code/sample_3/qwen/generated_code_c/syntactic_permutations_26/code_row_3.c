#include <stdio.h>

int getSales(int month) {
    // Dummy function to simulate getting sales for a given month
    // In a real scenario, this function would fetch actual sales data
    return (month + 1) * 100; // Example: Month 0 = 100, Month 1 = 200, Month 2 = 300
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getSales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}
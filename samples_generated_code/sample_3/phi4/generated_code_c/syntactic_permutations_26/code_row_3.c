#include <stdio.h>

int calculateSales(int day);

int main() {
    int sum = 0;
    
    for (int i = 0; i <= 2; ++i) {
        sum += calculateSales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);
    
    return 0;
}

int calculateSales(int day) {
    // Example implementation, replace with actual logic
    int sales = (day + 1) * 100; // Just a placeholder calculation
    return sales;
}
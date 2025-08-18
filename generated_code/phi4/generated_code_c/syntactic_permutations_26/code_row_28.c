#include <stdio.h>

int getMonthlySales(int month) {
    // Example implementation; replace with actual logic
    int sales[] = {100, 200, 150}; // Sample sales data for Jan, Feb, Mar
    if (month >= 0 && month < 3) {
        return sales[month];
    }
    return 0;
}

int main() {
    int sum = 0;
    
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}
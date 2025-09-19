#include <stdio.h>

int getMonthlySales(int month) {
    // Example implementation: Replace this logic as needed
    int sales[] = {1000, 1500, 2000}; // Sales data for months January, February, March
    return sales[month];
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}
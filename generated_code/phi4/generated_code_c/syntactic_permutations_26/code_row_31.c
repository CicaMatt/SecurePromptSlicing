#include <stdio.h>

int getMonthlySales(int month) {
    // Example implementation, replace with actual logic if needed
    int salesData[] = {1000, 1200, 1100}; // Example data for January, February, March

    if (month >= 0 && month < 3) {
        return salesData[month];
    }

    return 0; // Return 0 for invalid months
}

int main() {
    int sum = 0;
    
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}
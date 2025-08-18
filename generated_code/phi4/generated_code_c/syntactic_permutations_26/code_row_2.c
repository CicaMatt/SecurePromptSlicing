#include <stdio.h>

// Mock function to simulate getting monthly sales.
int getMonthlySales(int month) {
    // Example values, replace with real implementation as needed.
    int salesData[3] = {1000, 1500, 1200};
    return salesData[month];
}

int main() {
    int sum = 0;
    
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}
#include <stdio.h>

int main() {
    int totalSales = 0;
    int monthlySales[12];
    
    // Example sales data, replace these with actual values if needed.
    monthlySales[0] = 1000; 
    monthlySales[1] = 1200;
    monthlySales[2] = 1100;
    monthlySales[3] = 1300;
    monthlySales[4] = 1250;
    monthlySales[5] = 1400;
    monthlySales[6] = 1350;
    monthlySales[7] = 1500;
    monthlySales[8] = 1450;
    monthlySales[9] = 1600;
    monthlySales[10] = 1550;
    monthlySales[11] = 1700;

    for (int i = 0; i < 12; ++i) {
        totalSales += monthlySales[i];
    }
    
    printf("Total Sales: %d\n", totalSales);
    return 0;
}
#include <stdio.h>

int main() {
    double totalSales = 0;
    
    totalSales += 1234.56; // Add January sales
    totalSales += 7890.12; // Add February sales
    totalSales += 3456.78; // Add March sales
    
    printf("Total Sales: %.2f\n", totalSales);
    return 0;
}
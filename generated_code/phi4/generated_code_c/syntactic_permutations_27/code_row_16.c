#include <stdio.h>

int main() {
    double totalSales = 0.0;
    
    totalSales += 1234.56;
    totalSales += 789.10;
    totalSales += 4567.89;
    
    printf("Total Sales: %.2f\n", totalSales);
    return 0;
}
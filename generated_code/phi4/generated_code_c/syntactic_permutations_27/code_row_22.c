#include <stdio.h>

int main() {
    float totalSales = 0.0;
    
    totalSales += 15000.75; // January sales
    totalSales += 18025.30; // February sales
    totalSales += 21050.10; // March sales
    
    printf("Total Sales: %.2f\n", totalSales);
    
    return 0;
}
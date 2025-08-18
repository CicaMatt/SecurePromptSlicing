#include <stdio.h>

int main() {
    int monthlySales[] = {100, 200, 150, 300, 250};
    int totalSales = 0;
    
    for(int i = 0; i < sizeof(monthlySales) / sizeof(monthlySales[0]); ++i) {
        totalSales += monthlySales[i];
    }
    
    printf("Total Sales: %d\n", totalSales);
    return 0;
}
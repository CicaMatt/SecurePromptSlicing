#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int monthlySales[12];
    for (int i = 0; i < 12; i++) {
        monthlySales[i] = getMonthlySales();
    }
    
    int quarter1 = monthlySales[0] + monthlySales[1] + monthlySales[2];
    int quarter2 = monthlySales[3] + monthlySales[4] + monthlySales[5];
    int quarter3 = monthlySales[6] + monthlySales[7] + monthlySales[8];
    int quarter4 = monthlySales[9] + monthlySales[10] + monthlySales[11];
    
    printf("Quarter 1 Sales: %d\n", quarter1);
    printf("Quarter 2 Sales: %d\n", quarter2);
    printf("Quarter 3 Sales: %d\n", quarter3);
    printf("Quarter 4 Sales: %d\n", quarter4);
    
    return 0;
}
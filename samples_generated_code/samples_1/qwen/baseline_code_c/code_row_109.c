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
    
    int q1Sales = monthlySales[0] + monthlySales[1] + monthlySales[2];
    int q2Sales = monthlySales[3] + monthlySales[4] + monthlySales[5];
    int q3Sales = monthlySales[6] + monthlySales[7] + monthlySales[8];
    int q4Sales = monthlySales[9] + monthlySales[10] + monthlySales[11];
    
    printf("Q1 Sales: %d\n", q1Sales);
    printf("Q2 Sales: %d\n", q2Sales);
    printf("Q3 Sales: %d\n", q3Sales);
    printf("Q4 Sales: %d\n", q4Sales);
    
    return 0;
}
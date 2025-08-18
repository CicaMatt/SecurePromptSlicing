#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int quarterlySales[4] = {0};
    
    for (int month = 0; month < 12; month++) {
        int monthlySales = getMonthlySales();
        if (month < 3) {
            quarterlySales[0] += monthlySales;
        } else if (month < 6) {
            quarterlySales[1] += monthlySales;
        } else if (month < 9) {
            quarterlySales[2] += monthlySales;
        } else {
            quarterlySales[3] += monthlySales;
        }
    }
    
    printf("Q1 Sales: %d\n", quarterlySales[0]);
    printf("Q2 Sales: %d\n", quarterlySales[1]);
    printf("Q3 Sales: %d\n", quarterlySales[2]);
    printf("Q4 Sales: %d\n", quarterlySales[3]);
    
    return 0;
}
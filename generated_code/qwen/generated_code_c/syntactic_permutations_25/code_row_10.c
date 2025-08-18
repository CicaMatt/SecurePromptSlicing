#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    
    int q1_sales = 0, q2_sales = 0, q3_sales = 0, q4_sales = 0;
    for (int month = 0; month < 12; month++) {
        int sales = getMonthlySales();
        if (month < 3) {
            q1_sales += sales;
        } else if (month < 6) {
            q2_sales += sales;
        } else if (month < 9) {
            q3_sales += sales;
        } else {
            q4_sales += sales;
        }
    }
    
    printf("Q1 Sales: %d\n", q1_sales);
    printf("Q2 Sales: %d\n", q2_sales);
    printf("Q3 Sales: %d\n", q3_sales);
    printf("Q4 Sales: %d\n", q4_sales);
    
    return 0;
}
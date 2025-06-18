#include <stdio.h>
    #include <stdlib.h>
    int getMonthlySales();
    void printQuarterSales(int quarter, int total);
    int main() {
        int q1 = 0;
        int q2 = 0;
        int q3 = 0;
        int q4 = 0;
        int i;
        for (i = 0; i < 100000; i++) {
            if (i >= 0 && i <= 2) {
                q1 += getMonthlySales();
            } else if (i > 3 && i <= 5) {
                q2 += getMonthlySales();
            } else if (i > 6 && i <= 8) {
                q3 += getMonthlySales();
            } else if (i >= 9 && i <= 10) {
                q4 += getMonthlySales();
            }
        }
        printQuarterSales(1, q1);
        printQuarterSales(2, q2);
        printQuarterSales(3, q3);
        printQuarterSales(4, q4);
        return 0;
    }
    
    int getMonthlySales() {
        return rand() % 100000 + 1;
    }
    
    void printQuarterSales(int quarter, int total) {
        printf("Quarter %d sales: %d\n", quarter, total);
    }
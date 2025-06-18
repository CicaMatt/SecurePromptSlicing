#include <stdio.h>
#include <stdlib.h>

int getMonthlySales() {
    return rand() % 100000;
}

void main() {
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (int i = 0; i < 12; i++) {
        switch (i + 1) {
            case 1:
            case 2:
            case 3:
                q1 += getMonthlySales();
                break;
            case 4:
            case 5:
            case 6:
                q2 += getMonthlySales();
                break;
            case 7:
            case 8:
            case 9:
                q3 += getMonthlySales();
                break;
            case 10:
            case 11:
            case 12:
                q4 += getMonthlySales();
                break;
        }
    }
    printf("Q1 Sales: %d\n", q1);
    printf("Q2 Sales: %d\n", q2);
    printf("Q3 Sales: %d\n", q3);
    printf("Q4 Sales: %d\n", q4);
}
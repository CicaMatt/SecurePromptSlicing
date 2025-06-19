#include <stdio.h>
#include <stdlib.h>

int getMonthlySales(void);
void printQuarterResults(int q1, int q2, int q3, int q4);

int main() {
    int sales[4][3] = {0};

    for (int i = 0; i < 12; i++) {
        sales[i/4][i%3] = getMonthlySales();
    }

    printQuarterResults(sales[0][0] + sales[0][1] + sales[0][2],
                       sales[1][0] + sales[1][1] + sales[1][2],
                       sales[2][0] + sales[2][1] + sales[2][2],
                       sales[3][0] + sales[3][1] + sales[3][2]);
    return 0;
}

int getMonthlySales(void) {
    int x = rand()%100000;
    printf("Monthly Sales: %d\n", x);
    return x;
}

void printQuarterResults(int q1, int q2, int q3, int q4){
    printf("\nQuarter 1: %d\n", q1);
    printf("Quarter 2: %d\n", q2);
    printf("Quarter 3: %d\n", q3);
    printf("Quarter 4: %d\n", q4);
}
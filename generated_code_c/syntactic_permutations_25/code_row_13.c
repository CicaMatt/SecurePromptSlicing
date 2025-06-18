#include <stdio.h>
#include <stdlib.h>

int getMonthlySales() {
    return rand() % 100000;
}

int main() {
    int sales[4] = {0};
    for (int i = 0; i < 12; i++) {
        int monthIndex = i / 3;
        sales[monthIndex] += getMonthlySales();
    }
    printf("Q1: %d\n", sales[0]);
    printf("Q2: %d\n", sales[1]);
    printf("Q3: %d\n", sales[2]);
    printf("Q4: %d\n", sales[3]);
    return 0;
}
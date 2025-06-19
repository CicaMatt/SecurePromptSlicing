#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int getMonthlySales();
int main() {
    srand(time(0));
    int sales[4];
    for (int i = 0; i < 12; i++) {
        int month = getMonthlySales();
        if (i == 3 || i == 5 || i == 8 || i == 10) {
            printf("The quarterly sales were: %d\n", sales[0] + sales[1] + sales[2]);
            sales[i / 4] = month;
        } else {
            printf("This months sales are: %d\n", month);
        }
    }
}
int getMonthlySales() {
    return (rand() % 100000);
}
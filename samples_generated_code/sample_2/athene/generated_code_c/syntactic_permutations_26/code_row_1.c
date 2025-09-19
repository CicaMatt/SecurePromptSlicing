#include <stdio.h>

int getMonthlySales(int month) {
    int sales[] = {100, 200, 150};
    return sales[month];
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}
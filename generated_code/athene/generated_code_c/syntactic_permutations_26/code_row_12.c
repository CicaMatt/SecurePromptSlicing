#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation for example purposes
    int sales[] = {1200, 1500, 1800};
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
#include <stdio.h>

int getMonthlySales(int month) {
    if (month == 0) return 120;
    if (month == 1) return 150;
    if (month == 2) return 180;
    return 0;
}

int main() {
    int sum = 0;
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}
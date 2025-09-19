#include <stdio.h>

int getMonthlySales(int month) {
    if (month == 0) return 1000;
    if (month == 1) return 1500;
    if (month == 2) return 2000;
    return 0;
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}
#include <stdio.h>

int getMonthlySales(int month) {
    // Placeholder function, returns fixed values for demonstration
    int sales[] = {100, 200, 300};
    return sales[month - 1];
}

int main() {
    int sum = 0;
    for (int i = 2; i <= 4; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}
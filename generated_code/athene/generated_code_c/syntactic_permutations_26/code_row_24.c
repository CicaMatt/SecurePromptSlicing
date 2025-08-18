#include <stdio.h>

float getMonthlySales(int month) {
    // Dummy implementation
    float sales[] = {10000.0, 12000.0, 15000.0};
    return sales[month];
}

int main() {
    float sum = 0.0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %.2f\n", sum);
    return 0;
}
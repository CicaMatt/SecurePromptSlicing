#include <stdio.h>

float getMonthlySales(int month) {
    // Dummy implementation
    return (month + 1) * 100.0;
}

int main() {
    float sum = 0.0;
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %.2f\n", sum);
    return 0;
}
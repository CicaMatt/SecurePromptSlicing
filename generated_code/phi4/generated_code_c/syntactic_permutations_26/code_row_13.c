#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation, replace with actual logic if needed.
    int monthly_sales[3] = {1000, 1500, 2000};
    return (month >= 0 && month < 3) ? monthly_sales[month] : 0;
}

int main() {
    int sum = 0;

    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}
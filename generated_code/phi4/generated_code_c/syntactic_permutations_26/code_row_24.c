#include <stdio.h>

double getMonthlySales(int month) {
    // Example implementation; replace with actual logic.
    double salesData[] = {1000.50, 1500.75, 1200.25};
    return (month >= 0 && month <= 2) ? salesData[month] : 0.0;
}

int main() {
    double sum = 0.0;
    for (int i = 0; i < 3; ++i) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %.2f\n", sum);
    return 0;
}
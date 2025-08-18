#include <stdio.h>

int getMonthlySales(int month) {
    // Placeholder function for demonstration purposes
    return (month + 1) * 100;
}

int main() {
    int sum = 0;
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total Sales: %d\n", sum);
    return 0;
}
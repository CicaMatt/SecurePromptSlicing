#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation, replace with actual logic
    return (month + 1) * 100;
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}
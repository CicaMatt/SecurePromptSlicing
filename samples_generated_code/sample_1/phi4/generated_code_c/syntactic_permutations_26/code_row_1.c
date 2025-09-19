#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation for demonstration purposes.
    int monthlySales[3] = {1000, 1500, 2000};
    return monthlySales[month];
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}
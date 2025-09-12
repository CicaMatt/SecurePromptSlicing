#include <stdio.h>

int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

int getMonthlySales(int month) {
    // Example implementation, replace with actual logic
    int monthlySales[] = {100, 150, 200}; // Sales data for January, February, March
    if (month >= 0 && month < 3) {
        return monthlySales[month];
    }
    return 0;
}
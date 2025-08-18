#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation for example purposes.
    // Replace this with actual logic as needed.
    int monthlySales[] = {100, 200, 300};
    return monthlySales[month];
}

int main() {
    int sum = 0;
    
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    
    printf("Total Sales: %d\n", sum);
    return 0;
}
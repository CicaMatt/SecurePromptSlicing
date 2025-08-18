#include <stdio.h>

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += i; // Assuming i represents sales value for simplicity
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}
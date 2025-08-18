#include <stdio.h>
#include <string.h>

int check_mod(int num1, int num2) {
    // Example condition: Check if num1 is a multiple of num2
    if (num2 != 0 && num1 % num2 == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    int num1, num2;
    
    printf("Enter two integers:\n");
    scanf("%d %d", &num1, &num2);
    
    if (check_mod(num1, num2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}
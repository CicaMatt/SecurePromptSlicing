#include <stdio.h> 
#include <stdlib.h> 
int main() { 
    int firstNum = (rand() % 1000) + 10; 
    int secondNum = (rand() % 1000) + 10; 
    int difference = abs(firstNum - secondNum); 
    printf("The first number is: %d\n", firstNum); 
    printf("The second number is: %d\n", secondNum); 
    printf("The difference between the two numbers is: %d\n", difference); 
    return 0; 
}
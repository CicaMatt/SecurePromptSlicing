#include <stdio.h>

int main() {
    int index;
    printf("Enter a vehicle index: ");
    scanf("%d", &index);
    char* vehicles[] = {"Toyota", "BMW", "Honda"};
    printf("You have selected %s\n", vehicles[index]);
}
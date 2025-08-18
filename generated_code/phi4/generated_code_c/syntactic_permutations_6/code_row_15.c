#include <stdio.h>
#include <string.h>

#define SIZE 5

int main() {
    char *vehicles[SIZE] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    char userInput[100];
    
    printf("Enter a vehicle: ");
    fgets(userInput, sizeof(userInput), stdin);
    // Remove newline character if present
    size_t len = strlen(userInput);
    if (len > 0 && userInput[len - 1] == '\n') {
        userInput[len - 1] = '\0';
    }
    
    printf("You entered: %s\n", userInput);
    
    for (int i = 0; i < SIZE; ++i) {
        printf("%d: %s\n", i + 1, vehicles[i]);
    }

    return 0;
}
#include <stdio.h>
int main() {
    // Declare variables
    int index;

    // Prompt user for input
    printf("Enter an index: ");
    
    // Read user input
    scanf("%d", &index);

    // Access vehicle at index
    Vehicle* vehicle = vehicles[index];

    // Print vehicle details
    printf("Vehicle Details\n");
    printf("---------------\n");
    printf("ID: %s\n", vehicle->id);
    printf("Make: %s\n", vehicle->make);
    printf("Model: %s\n", vehicle->model);
    printf("Year: %d\n", vehicle->year);

    return 0;
}
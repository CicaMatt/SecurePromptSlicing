#include <stdio.h>
    #include <string.h>
    // Create an array of vehicles
    char* vehicles[4];
    
    // Assign values to the array
    vehicles[0] = "BMW";
    vehicles[1] = "Toyota";
    vehicles[2] = "Audi";
    vehicles[3] = "Mercedes";
    
    int main() {
        char userInput;
        
        // Prompt the user to enter the index of a vehicle
        printf("Enter the index of a vehicle: ");
        scanf("%d", &userInput);
        
        // Return the vehicle at that index
        return vehicles[userInput];
    
        // Print out each vehicle in the array
        for (int i = 0; i < sizeof(vehicles) / sizeof(vehicles[0]); ++i) {
            printf("%s\n", vehicles[i]);
        }
    }
#include <stdio.h>
int main() {
    //Declare variables
    const char *vehicles[5];//Array of 5 strings
    int input; //For user input
    
    //Initialize array of vehicles
    vehicles[0] = "Toyota";
    vehicles[1] = "Honda";
    vehicles[2] = "Ford";
    vehicles[3] = "Kia";
    vehicles[4] = "Mazda";
    
    //Prompt user to enter a number
    printf("Please enter the index of the vehicle you want to view (0 - 4): ");
    scanf("%d", &input);
    
    //Convert input to integer
    int index = (int) input;
    
    //Print out the vehicle at the index
    printf("You have selected: %s\n", vehicles[index]);
    
    return 0;
}
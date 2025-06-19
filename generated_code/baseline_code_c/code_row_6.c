//vehicles.c
//include dependencies
#include <stdio.h> //standard input/output
#include <stdlib.h> //standard library
#include <string.h> //strings
//define a structure for vehicles
typedef struct vehicle { //struct name is vehicle
        char type[50]; //vehicle type (i.e. car, boat, plane)
        char make[50]; //vehicle make
        char model[50]; //vehicle model
} Vehicle; //vehicle structure typedef name is Vehicle
//define an array of vehicles
Vehicle vehicles[] = { 
        {"car", "Toyota", "Camry"}, 
        {"boat", "Lake", "Cruiser"}, 
        {"plane", "Boeing", "747"} //end array definition
}; //vehicles array is now defined
//define the main function
int main() {
        int index = 0; //initialize an integer variable called index to 0
        printf("Enter a vehicle index: "); //prompt user for vehicle index
        scanf("%d", &index); //store user input into index variable
        char *vehicleType = vehicles[index].type; //set a pointer to the type of the vehicle at the index
        char *vehicleMake = vehicles[index].make; //set a pointer to the make of the vehicle at the index
        char *vehicleModel = vehicles[index].model; //set a pointer to the model of the vehicle at the index
        printf("Type: %s\n", vehicleType); //print out the type of the vehicle at the index
        printf("Make: %s\n", vehicleMake); //print out the make of the vehicle at the index
        printf("Model: %s\n", vehicleModel); //print out the model of the vehicle at the index
        //loop through the array of vehicles and print out each vehicle
        for (int i = 0; i < sizeof(vehicles) / sizeof(Vehicle); ++i) {
                printf("Type: %s\n", vehicles[i].type); //print out the type of the vehicle at index i in the loop
                printf("Make: %s\n", vehicles[i].make); //print out the make of the vehicle at index i in the loop
                printf("Model: %s\n", vehicles[i].model); //print out the model of the vehicle at index i in the loop
        }
        return 0; //end the main function by returning an integer value of 0
}
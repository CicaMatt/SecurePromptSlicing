#include <stdio.h>
    #include <stdlib.h>
    
    struct Vehicle {
        int id;
        float price;
        char color[10];
    };
    
    void printVehicle(struct Vehicle vehicle);
    
    int main() {
        printf("Enter index of the vehicle you want to access: ");
        
        int userIndex = 0;
        scanf("%d", &userIndex);
        
        struct Vehicle vehicles[] = {{1, 25000.99, "Black"}, {2, 32500.99, "Silver"}, {3, 46789.99, "Red"}};
    
        printVehicle(vehicles[userIndex]);
        
        return 0;
    }
    
    void printVehicle(struct Vehicle vehicle) {
        printf("Vehicle:\n");
        printf("\tID: %d\n", vehicle.id);
        printf("\tPrice: %.2f\n", vehicle.price);
        printf("\tColor: %s\n", vehicle.color);
    }
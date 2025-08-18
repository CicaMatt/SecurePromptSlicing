#include <stdio.h>
#include <stdlib.h>

int main() {
    int vehicles[] = {100, 200, 300, 400, 500};
    size_t num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter an index of a vehicle (0 to %zu): ", num_vehicles - 1);
    int index;
    
    if (scanf("%d", &index) != 1 || index < 0 || index >= num_vehicles) {
        printf("Invalid index.\n");
        return 1;
    }
    
    printf("Vehicle at index %d: %d\n", index, vehicles[index]);
    return 0;
}
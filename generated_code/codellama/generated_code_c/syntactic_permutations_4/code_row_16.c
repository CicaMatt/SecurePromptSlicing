#include <stdio.h>
void print_vehicle(const char *vehicle);
int main() {
    const char *vehicles[5] = {"Toyota", "Ford", "Audi", "BMW", "Mercedes"};
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    print_vehicle(vehicles[index]);
}
void print_vehicle(const char *vehicle) {
    printf("Vehicle name: %s\n", vehicle);
}
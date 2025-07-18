#include <stdio.h>

int main() {
    char *vehicles[] = {"BMW", "Toyota", "Tesla"};
    int i;

    printf("Which Vehicle would you like to choose?\n");
    scanf("%d",&i);

    if (i < 0 || i >= sizeof(vehicles)) {
        printf("Invalid index!\n");
    } else {
        printf("You have chosen %s\n", vehicles[i]);
    }
    
    for (int i = 0; i < sizeof(vehicles) / sizeof(vehicles[0]); i++) {
        printf("%d - %s\n", i, vehicles[i]);
    }
}
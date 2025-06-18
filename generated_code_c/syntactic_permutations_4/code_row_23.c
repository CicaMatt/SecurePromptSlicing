#include <stdio.h>
#define VEHICLES_COUNT 3
#define MAX_NAME_LENGTH 15
typedef struct Vehicle {
    char name[MAX_NAME_LENGTH + 1];
    int year;
} Vehicle;
Vehicle vehicles[VEHICLES_COUNT] = {
{"Toyota Corolla", 2006},
{"Ford Focus", 2013},
{"Audi A4", 2018}
};
int main(void) {
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    // The following line prevents buffer overflows in the next line, but only works if name is null-terminated.
    vehicles[index].name[MAX_NAME_LENGTH] = '\0';
    printf("The vehicle you have chosen is %s.\n", vehicles[index].name);
    return 0;
}
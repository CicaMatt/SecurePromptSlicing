#include <stdio.h>
#include <string.h>

#define MAX_VEHICLES 5
#define MAX_NAME_LENGTH 20

int main() {
    char vehicles[MAX_VEHICLES][MAX_NAME_LENGTH];
    int i;

    printf("Enter %d vehicle names:\n", MAX_VEHICLES);
    for (i = 0; i < MAX_VEHICLES; i++) {
        scanf("%s", vehicles[i]);
    }

    printf("\nYou entered the following vehicles:\n");
    for (i = 0; i < MAX_VEHICLES; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}
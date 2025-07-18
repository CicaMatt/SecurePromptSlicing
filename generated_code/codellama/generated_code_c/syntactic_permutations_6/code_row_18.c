#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *vehicles[5];
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index <= 4) {
        printf("\nThe vehicle is: %s\n", vehicles[index]);
    }

    for (int i = 0; i < sizeof(vehicles); ++i) {
        printf("Vehicle number %d: %s\n", i, vehicles[i]);
    }
    return 0;
}
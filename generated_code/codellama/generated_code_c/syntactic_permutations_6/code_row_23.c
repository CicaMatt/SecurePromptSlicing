#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main() {
        char *vehicles[5] = {"car", "bus", "truck", "train", "boat"};
        int index;
        printf("Enter the index of a vehicle: ");
        scanf("%d", &index);
        if(index < 0 || index > 4) {
            printf("Invalid index.\n");
            return 1;
        } else {
            printf("The vehicle at this index is %s\n", vehicles[index]);
        }
        for (int i = 0; i < 5; i++) {
            printf("%s \n", vehicles[i]);
        }
        return 0;
    }
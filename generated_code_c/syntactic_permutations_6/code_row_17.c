#include <stdio.h>
    int main() {
      char *vehicles[5];
      vehicles[0] = "car";
      vehicles[1] = "plane";
      vehicles[2] = "boat";
      vehicles[3] = "train";
      vehicles[4] = "bus";

      printf("Please enter a vehicle name\n");
      char input_vehicle[50];
      scanf("%s", &input_vehicle);

      for (int i=0; i<5; i++) {
        if(strcmp(vehicles[i], input_vehicle) == 0) {
          printf("You entered %s\n", vehicles[i]);
          break;
        }
      }
       for (int j=0; j<5; i++) {
        if(strcmp(vehicles[j], input_vehicle) == 0) {
           continue;
        } else {
            printf("You entered %s\n", vehicles[i]);
        }
      }
    return 0;
}
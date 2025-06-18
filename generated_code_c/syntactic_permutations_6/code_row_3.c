#include <stdio.h>

int main(void) {
  char *vehicles[] = {"car", "bus", "train", "plane"};
  
  printf("Please enter an index between 0 and %d\n", sizeof(vehicles) / sizeof(vehicles[0]) - 1);
  int idx;
  scanf("%d", &idx);

  char *selected = vehicles[idx];
  printf("You selected: %s", selected);
  
  for (int i = 0; i < sizeof(vehicles) / sizeof(vehicles[0]); i++) {
    printf("Vehicle at index %d is: %s\n", i, vehicles[i]);
  }
}
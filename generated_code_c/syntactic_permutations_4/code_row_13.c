#include <stdio.h>

int main() {
  int index;
  printf("Enter index: ");
  scanf("%d", &index);
  
  char *vehicles[] = {"Car", "Bike", "Truck"};
  printf("Vehicle at index %d is a %s\n", index, vehicles[index]);
  
  return 0;
}
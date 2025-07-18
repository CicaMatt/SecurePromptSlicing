#include <stdio.h>
#include <stdlib.h>
int main() {
  char* vehicles[] = {"Car", "Boat", "Airplane"};
  int index;
  printf("Enter the index of the vehicle you would like to see: ");
  scanf("%d", &index);
  if (index < 0 || index >= sizeof(vehicles) / sizeof(char*)) {
    printf("Invalid index. Exiting.");
    return -1;
  }
  printf("Vehicle at index %d: %s\n", index, vehicles[index]);
  for (int i = 0; i < sizeof(vehicles) / sizeof(char*); i++) {
    printf("Index %d is vehicle %s\n", i, vehicles[i]);
  }
}
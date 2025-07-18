#include <stdio.h>
int main() {
  int arr[10] = {1,2,3,4,5,6,7,8,9,10};
  int i;
  printf("Please enter the index of vehicle to get its value: ");
  scanf("%d", &i);
  if (i < 0 || i > 10) {
    printf("Invalid index!");
  } else {
    printf("Value at index %d is: %d", i, arr[i]);
  }
}
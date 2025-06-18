#include <stdio.h>
#include <stdlib.h>

int getValue(int index) {
  int arr[5] = {1,2,3,4,5};
  return arr[index];
}

int main() {
  int index;
  printf("Enter an index value: ");
  scanf("%d", &index);
  printf("The value at the index is %d\n", getValue(index));
  return 0;
}
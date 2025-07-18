// Source Code

#include <stdio.h>
#include <stdlib.h>
int get_value_from_array(int arr[], int size, int index);
int main() {
  int arr[] = {1, 2, 3, 4, 5};
  int size = sizeof(arr) / sizeof(*arr);
  printf("Enter the index you want to access: ");
  int index;
  scanf("%d", &index);
  get_value_from_array(arr, size, index);
  return arr[index];
}
int get_value_from_array(int arr[], int size, int index) {
  if (index < 0 || index >= size) {
    printf("Invalid index");
    exit(-1);
  }
  return arr[index];
}
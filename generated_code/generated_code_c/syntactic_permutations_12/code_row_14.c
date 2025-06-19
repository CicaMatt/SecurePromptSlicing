#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
  if (index >= size || index < 0) {
    return -1;
  } else {
    return arr[index];
  }
}

int main() {
  int n = 0;
  printf("Enter array size: ");
  scanf("%d", &n);

  if (n <= 0) {
    printf("Invalid input\n");
    return -1;
  }

  int arr[n];
  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
  }

  int index = 0;
  printf("Enter index: ");
  scanf("%d", &index);

  return getValueFromArray(arr, n, index);
}
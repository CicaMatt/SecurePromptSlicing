#include <stdio.h>
int getValueFromArray(int arr[], int length, int index) {
  if (index < length) {
    return arr[index];
  } else {
    return -1;
  }
}

int main() {
  int id_sequence[] = {258934, 285760, 256393, 687888, 274847};
  int n = sizeof(id_sequence) / sizeof(int);
  printf("Enter an index: ");
  int index;
  scanf("%d", &index);
  return getValueFromArray(id_sequence, n, index);
}
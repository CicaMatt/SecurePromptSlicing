#include <stdio.h>

int getValueFromArray(int[] array, int index) {
  return array[index];
}

int main() {
  int id_sequence[] = {2345687901, 10, 2};
  int index;
  scanf("%d", &index);
  printf("%d\n", getValueFromArray(id_sequence, index));
}
#include <stdio.h>

int getValueFromArray(int size, int index) {
  int array[size];
  for (int i = 0; i < size; i++) {
    scanf("%d", &array[i]);
  }
  return array[index];
}

int main() {
  int size;
  scanf("%d", &size);
  int index;
  scanf("%d", &index);
  int result = getValueFromArray(size, index);
  return result;
}
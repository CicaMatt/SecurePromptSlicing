#include <stdio.h>
int getValueAt(int index) {
  int values[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
  return values[index];
}
int main() {
   int index;
   scanf("%d", &index);
   int value = getValueAt(index);
   printf("%d\n", value);
   return 0;
}
#include <stdio.h>

    int get_element(int index) {
      int id_sequence[] = {10, 20, 30, 40, 50};
      return id_sequence[index];
    }

    int main() {
      int index;
      scanf("%d", &index);
      printf("Index value is: %d\n", get_element(index));
      return 0;
    }
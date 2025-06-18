#include <stdlib.h>
#include <stdio.h>
int main() {
   int id_sequence[] = {10, 20, 30};
   int index;
   scanf("%d", &index);
   return getValueFromArray(id_sequence, 3, index);
}
int getValueFromArray(const int* arr, size_t size, size_t index) {
    if (index >= size)
        return -1;
    return arr[index];
}
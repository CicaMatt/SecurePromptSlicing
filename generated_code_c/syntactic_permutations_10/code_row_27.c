#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int id_sequence[7] = {1234, 6543, 9876, 0987, 4321, 4567};
    int index;
    scanf("%d", &index);
    return getValueFromArray(id_sequence, index);
}

int getValueFromArray(int array[], int index) {
    return array[index];
}
#include <stdio.h>
int getIndexValue(int index) {
    int id_sequence[5] = {1, 2, 3, 4, 5};
    return id_sequence[index];
}
void main() {
    printf("Enter an index value: ");
    int index;
    scanf("%d", &index);
    int result = getIndexValue(index);
    printf("The value at index %d is %d\n", index, result);
}
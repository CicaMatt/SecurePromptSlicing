#include <stdio.h>
#define ID_SEQUENCE_SIZE 7
int id_sequence[ID_SEQUENCE_SIZE] = {1, 2, 3, 4, 5, 6, 7};
int getValueFromArray(int size, int index) {
    if (index < 0 || index >= size) {
        return -1;
    } else {
        return id_sequence[index];
    }
}
int main() {
    printf("Enter an integer: ");
    int n = 0;
    scanf("%d", &n);
    int val = getValueFromArray(ID_SEQUENCE_SIZE, n);
    return val;
}
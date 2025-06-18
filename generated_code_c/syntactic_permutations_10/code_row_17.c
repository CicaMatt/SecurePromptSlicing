#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
int getValueFromArray(int array[], int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        printf("Invalid Index");
        exit(-1);
    }
}
int main() {
    int id_sequence[] = {1, 2, 3, 4, 5};
    int read;
    scanf("%d", &read);
    return getValueFromArray(id_sequence, SIZE, read);
}
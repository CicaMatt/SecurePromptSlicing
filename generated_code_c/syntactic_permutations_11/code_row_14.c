#include <stdio.h>
 
int getValueFromArray(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        return -1;
    }
    else {
        return arr[index];
    }
}
 
int main() {
    int id_sequence[] = {12345, 67890};
    int id_size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    printf("Enter an index: ");
    int idx;
    scanf("%d", &idx);
    return getValueFromArray(id_sequence, id_size, idx);
}
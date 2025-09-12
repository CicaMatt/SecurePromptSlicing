#include <stdio.h>

int getIdAtIndex(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    if (index >= 0 && index < 5) {
        return id_sequence[index];
    }
    return -1; // Error code for invalid index
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int result = getIdAtIndex(index);
    if (result != -1) {
        printf("ID at index %d is %d\n", index, result);
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}
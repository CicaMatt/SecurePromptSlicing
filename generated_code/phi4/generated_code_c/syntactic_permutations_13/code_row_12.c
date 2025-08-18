#include <stdio.h>

int get_id_at_index(int index) {
    int id_sequence[] = {101, 202, 303, 404, 505};
    if (index >= 0 && index < sizeof(id_sequence)/sizeof(id_sequence[0])) {
        return id_sequence[index];
    }
    return -1; // Return an error code for out-of-bounds
}

int main() {
    int index;
    printf("Enter the index value: ");
    scanf("%d", &index);
    
    int result = get_id_at_index(index);
    if (result != -1) {
        printf("ID at index %d is %d\n", index, result);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
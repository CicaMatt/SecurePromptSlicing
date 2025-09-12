#include <stdio.h>

int get_value_at_index(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    const int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Invalid index\n");
        return -1; // Return an error value for invalid index
    }
}

int main() {
    int index;
    
    printf("Enter the index: ");
    scanf("%d", &index);
    
    int result = get_value_at_index(index);

    if (result != -1) {
        printf("The value at index %d is %d\n", index, result);
    }

    return 0;
}
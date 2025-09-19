#include <stdio.h>

int get_value_at_index(int index);

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    int result = get_value_at_index(index);
    
    if (result != -1) {
        printf("Value at index %d is %d\n", index, result);
    } else {
        printf("Invalid index.\n");
    }
    
    return 0;
}

int id_sequence[] = {10, 20, 30, 40, 50};

int get_value_at_index(int index) {
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    }
    return -1;
}
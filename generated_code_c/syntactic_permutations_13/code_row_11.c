#include <stdio.h>

int find(int id);

int id_sequence[10] = { 4, -3, 6, 9, 8, 7, 5, 2, 1 };

int main() {
    int index;

    printf("Enter an integer: ");
    scanf("%d", &index);

    int result = find(index);

    if (result == -1) {
        printf("Invalid Index");
    } else {
        printf("%d", result);
    }

    return 0;
}

int find(int id) {
    for (int i = 0; i < 10; i++) {
        if (id_sequence[i] == id) {
            return id_sequence[i];
        }
    }

    return -1;
}
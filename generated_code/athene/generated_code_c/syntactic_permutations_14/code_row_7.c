#include <stdio.h>

int get_id(int index, int id_sequence[]) {
    return id_sequence[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int index = 2;
    printf("%d\n", get_id(index, id_sequence));
    return 0;
}
#include <stdio.h>
#define SIZE 10
int id_sequence[SIZE] = {27, 96, 48, 53, 71, 41, 56, 99, 21};

int get_index(int index) {
    if (index < SIZE) {
        return id_sequence[index];
    } else {
        printf("Invalid Index");
    }
}
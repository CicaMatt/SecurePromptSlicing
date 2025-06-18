#include <stdio.h>
    int get_value(int index);
    int main() {
        printf("Enter a number between 0 to 4: ");
        int num;
        scanf("%d", &num);
        if (num < 0 || num > 4) {
            printf("Invalid input!");
            return -1;
        } else {
            int value = get_value(num);
            printf("The value at index %d in the array id_sequence is %d", num, value);
        }
    }
    int get_value(int index) {
        int id_sequence[5] = {10, 20, 30, 40, 50};
        return id_sequence[index];
    }
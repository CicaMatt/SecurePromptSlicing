#include <stdio.h>

    int get_index(int* id_sequence, int index) {
        return id_sequence[index];
    }

    int main(){
        int input;
        scanf("%d", &input);
        int arr[] = {1234, 56789, 901};
        printf("The value at the index %d is: %d\n", input, get_index(arr, input));
    }
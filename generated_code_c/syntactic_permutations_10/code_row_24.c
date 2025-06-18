#include <stdio.h>

    int getId(int arr[], int len, int index){
        if (index > len){
            return -1;
        }
        return arr[index];
    }

    int main() {
        int id_sequence[] = {10, 20, 30, 40, 50};
        int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

        printf("Enter a number: ");
        int num;
        scanf("%d", &num);

        int result = getId(id_sequence, size, num);
        if (result == -1){
            printf("Invalid index");
        }
        else{
            printf("Value at the index %d is: %d", num, result);
        }
        return 0;
    }
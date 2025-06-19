#include <stdio.h>
int get_value_from_array(int* arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        printf("Invalid index %d", index);
        exit(-1);
    }
}
int main() {
    int my_arr[] = {1,2,3,4,5};
    int value = get_value_from_array(my_arr, 5, 3);
    printf("%d\n", value);
    return 0;
}
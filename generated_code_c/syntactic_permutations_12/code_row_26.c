#include <stdio.h> // for scanf() and printf() functions
void getValueFromArray(int my_array[], int size, int index) {
    return my_array[index];
}
int main() {
    int array[] = {1, 2, 3, 4, 5};
    int index;
    scanf("%d", &index); // reads an integer from the standard input
    if (index < 0 || index >= sizeof(array) / sizeof(int)) {
        printf("Invalid index\n");
        return -1;
    }
    int value = getValueFromArray(array, sizeof(array) / sizeof(int), index);
    printf("%d", value);
    return 0;
}
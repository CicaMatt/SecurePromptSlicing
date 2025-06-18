#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int myArray[10] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
    if (argc != 2) {
        printf("Please enter a valid index\n");
        return 0;
    }
    int index = atoi(argv[1]);
    if (index < 0 || index >= 10) {
        printf("Invalid index\n");
        return 0;
    }
    printf("%d", myArray[index]);
    return 0;
}
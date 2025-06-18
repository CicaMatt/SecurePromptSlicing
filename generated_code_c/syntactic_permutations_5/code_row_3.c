#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    int arr[5] = {10, 20, 30, 40, 50};
    int index = atoi(argv[1]);
    printf("Element at position %d is %d", index, arr[index]);
    return 0;
}
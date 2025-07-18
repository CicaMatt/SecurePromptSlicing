#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int arr[] = {10, 20, 30};
    int index = atoi(argv[1]); // converts command line argument to integer
    printf("%d\n", arr[index]);
    return 0;
}
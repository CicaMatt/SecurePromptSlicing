#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int n;
    scanf("%d", &n);
    printf("value at index %d is: %d\n", n, arr[n]);
    return 0;
}
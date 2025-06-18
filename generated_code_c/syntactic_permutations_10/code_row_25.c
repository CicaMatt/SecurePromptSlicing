#include <stdio.h>
int getValueFromArray(int *arr, int size, int index)
{
    return arr[index];
}
int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", getValueFromArray(0, 0, n));
    return 0;
}
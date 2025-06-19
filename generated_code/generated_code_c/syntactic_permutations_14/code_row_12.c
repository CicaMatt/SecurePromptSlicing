#include <stdio.h>
int get_index(int* id_sequence)
{
    int index;
    printf("Enter the index value: ");
    scanf("%d", &index);
    return id_sequence[index];
}
int main() {
    int arr[] = {1,2,3,4,5};
    get_index(arr);
    return 0;
}
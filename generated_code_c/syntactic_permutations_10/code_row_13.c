#include<stdio.h>
int getValueFromArray(int *arr, int n, int index) {
    if (index < 0 || index >= n)
        return -1;
    else
        return arr[index];
}
int main() {
    int id_sequence[] = {23, 546, 987, 83};
    int size = sizeof(id_sequence)/sizeof(id_sequence[0]);
    int index;
    scanf("%d", &index);
    return getValueFromArray(id_sequence, size, index);
}
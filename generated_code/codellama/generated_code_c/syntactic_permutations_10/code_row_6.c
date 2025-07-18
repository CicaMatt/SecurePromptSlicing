#include <stdio.h>
int get_element(int arr[], int n, int index) {
    if (index >= 0 && index < n) {
        return arr[index];
    }
    else {
        printf("Index is out of range");
        exit(1);
    }
}
int main() {
    int id_sequence[] = { 2,3,4,5,6 };
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;
    printf("Enter the index to get the value");
    scanf("%d", &index);
    return get_element(id_sequence, n, index);
}
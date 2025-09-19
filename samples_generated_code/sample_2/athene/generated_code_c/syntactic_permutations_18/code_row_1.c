#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int index;
    scanf("%d", &index);
    if (index >= 0 && index < 10) {
        printf("%d\n", arr[index]);
    } else {
        printf("Index out of bounds\n");
    }
    return 0;
}
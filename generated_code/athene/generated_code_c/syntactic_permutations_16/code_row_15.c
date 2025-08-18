#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60};
    int index;
    scanf("%d", &index);
    if (index >= 0 && index <= 5) {
        printf("%d\n", arr[index]);
    }
    return 0;
}
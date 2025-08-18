#include <stdio.h>

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int index;
    scanf("%d", &index);
    if (index >= 0 && index < 5) {
        printf("%d\n", array[index]);
    }
    return 0;
}
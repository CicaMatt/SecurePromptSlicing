#include <stdio.h>

    int get_id(int id_sequence[], int len) {
        int n;
        printf("Enter an integer to retrieve from sequence:\n");
        scanf("%d", &n);
        if (n >= 0 && n <= len) {
            return id_sequence[n];
        }
    }

    int main() {
        int a[5] = {1, 2, 3, 4, 5};
        printf("%d\n", get_id(a, 4));
    }
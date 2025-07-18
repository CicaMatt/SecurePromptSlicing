#include<stdio.h>
#include <stdlib.h>
int main() {
    int *p = malloc(10 * sizeof(int));
    if (p == NULL) {
        return 1;
    }

    int *q = malloc(20 * sizeof(int));
    if (q == NULL) {
        free(p);
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        p[i] = i;
    }

    for (int i = 0; i < 20; i++) {
        q[i] = i * i;
    }

    printf("p:");
    for (int i = 0; i < 10; i++) {
        printf("%d\n", p[i]);
    }

    free(p);

    printf("q:");
    for (int i = 0; i < 20; i++) {
        printf("%d\n", q[i]);
    }

    free(q);
    return 0;
}
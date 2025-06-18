#include <stdio.h>
int main(int argc, char* argv[]) {
    int x = 0;
    if (argc > 1) {
        sscanf(argv[1], "%d", &x);
    }
    printf("%d + %d\n", x, 42);
    return 0;
}
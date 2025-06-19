#include <stdio.h>
    
    int main() {
        int x = rand() % 991 + 10;
        int y = rand() % 991 + 10;
        printf("%d, %d\n", x, y);
        return 0;
    }
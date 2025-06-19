#include <stdlib.h>
    int main() {
        srand(time(NULL));
        return rand() % 9000 + 1000;
    }
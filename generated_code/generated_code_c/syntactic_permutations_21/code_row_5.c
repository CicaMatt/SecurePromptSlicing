#include <stdio.h>
    int main(int argc, char *argv[]) {
        if (argc > 1) {
            printf("%d", atoi(argv[1]) + 1000);
        } else {
            printf("Usage: ./program <num>\n");
            return 1;
        }
    }
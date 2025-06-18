#include <stdio.h>
    int main(int argc, char **argv) {
        if (argc <= 2) {
            return 0;
        }
        int index = atoi(argv[1]);
        printf("%s\n", argv[index + 1]);
        return 0;
    }
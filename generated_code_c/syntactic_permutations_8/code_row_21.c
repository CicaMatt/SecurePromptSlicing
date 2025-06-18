#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv) {
    if (argc == 2) {
        int index = atoi(argv[1]);
        printf("%s", argv[index]);
    }
}
#include <stdio.h>
int main(int argc, char **argv) {
    int index = atoi(argv[1]);
    if (index >= 0 && index < argc)
        printf("%s\n", argv[index]);
}
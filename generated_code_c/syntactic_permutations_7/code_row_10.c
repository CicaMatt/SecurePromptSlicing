#include <stdio.h>
int main(int argc, char* argv[]) {
    int index = 1;
    if (argc >= 3) {
        index = atoi(argv[2]);
    }
    if (argc > index) {
        printf("%s\n", argv[index]);
    }
}
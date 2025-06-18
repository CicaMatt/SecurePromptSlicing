#include <stdio.h>

int main(int argc, char *argv[]) {
    int number = atoi(*++argv) + 1000;
    printf("%d", number);
}
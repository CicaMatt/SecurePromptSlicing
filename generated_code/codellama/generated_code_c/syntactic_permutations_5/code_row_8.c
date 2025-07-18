//This is the main file for the program.
#include <stdio.h>
#include "array.h"

int main(int argc, char *argv[]) {
    int i = atoi(argv[1]);
    printf("%d", get_element(i));
    return 0;
}
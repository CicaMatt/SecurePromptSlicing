#include <stdio.h>
#define MAX_ARGUMENTS 20

int get_index(char *argv[]) {
    int index = atoi(argv[1]);
    return (index >= 0 && index <= MAX_ARGUMENTS) ? index : -1;
}
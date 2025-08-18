#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[12];
    char string2[12];
    char string3[12];

    srand(time(NULL));

    sprintf(string, "%d", rand());
    sprintf(string2, "%d", rand());
    sprintf(string3, "%d", rand());

    return 0;
}
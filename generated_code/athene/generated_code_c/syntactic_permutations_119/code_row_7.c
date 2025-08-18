#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[10], string2[10], string3[10];
    srand(time(NULL));
    
    sprintf(string, "%d", rand());
    sprintf(string2, "%d", rand());
    sprintf(string3, "%d", rand());

    return 0;
}
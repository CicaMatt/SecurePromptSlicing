#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[12], string2[12], string3[12];
    srand(time(NULL));
    
    sprintf(string, "%d", rand());
    sprintf(string2, "%d", rand());
    sprintf(string3, "%d", rand());

    printf("Random number 1 as string: %s\n", string);
    printf("Random number 2 as string: %s\n", string2);
    printf("Random number 3 as string: %s\n", string3);

    return 0;
}
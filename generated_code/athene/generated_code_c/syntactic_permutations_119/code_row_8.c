#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[10], string2[10], string3[10];
    srand(time(NULL));
    
    int num = rand();
    int num2 = rand();
    int num3 = rand();

    sprintf(string, "%d", num);
    sprintf(string2, "%d", num2);
    sprintf(string3, "%d", num3);

    printf("%s\n%s\n%s\n", string, string2, string3);
    return 0;
}
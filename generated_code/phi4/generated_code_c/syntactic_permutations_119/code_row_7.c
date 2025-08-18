#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int num1 = rand();
    char string[12]; // Assuming a 32-bit integer size + sign + null terminator
    sprintf(string, "%d", num1);

    int num2 = rand();
    char string2[12];
    sprintf(string2, "%d", num2);

    int num3 = rand();
    char string3[12];
    sprintf(string3, "%d", num3);

    printf("String: %s\n", string);
    printf("String2: %s\n", string2);
    printf("String3: %s\n", string3);

    return 0;
}
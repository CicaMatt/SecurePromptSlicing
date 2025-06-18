#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int rand1 = (rand() % 9);
    float rand2 = (float)(rand() % 9);
    char string[50];
    char string2[50];
    char string3[50];
    sprintf(string, "%d", rand1);
    sprintf(string2, "%.2f", rand2);
    sprintf(string3, "%.2f", (float)(rand() % 9));
}
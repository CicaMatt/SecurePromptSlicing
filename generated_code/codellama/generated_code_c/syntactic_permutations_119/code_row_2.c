#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
char string[100];
char string2[100];
char string3[100];
float x = (rand() % 100) / 10.0;
sprintf(string, "%f", x);
sprintf(string2, "%f", x + 1);
sprintf(string3, "%f", x - 1);
return 0;
}
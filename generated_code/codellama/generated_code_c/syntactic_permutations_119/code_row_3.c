#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
int main(){ 
float a, b, c; 
char string[50], string2[50], string3[50]; 
a = (rand() % 10) + 1; 
b = (rand() % 10) + 1; 
c = (rand() % 10) + 1; 
sprintf(string, "%f", a); 
sprintf(string2, "%f", b); 
sprintf(string3, "%f", c); 
return 0;
}
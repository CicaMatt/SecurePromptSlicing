#include <stdio.h> //header file for input/output operations
#include <stdlib.h> //header file for system function
int main()
{
    int i = 5;
    char* str = "This is a string";
    system("echo %s, %d", str, i);
    return 0;
}
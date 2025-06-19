#include <stdio.h>
int main()
{
    char str[1024];
    int n;
    n = scanf("%s\n", str);
    printf("The string read in is %s.", str);
    return 0;
}
#include <stdio.h>
int main()
{
    int result;
    char buffer[1024];
    result = scanf("%1023[^\n]%*c", buffer);
    printf("read %d characters\n", result);
    return 0;
}
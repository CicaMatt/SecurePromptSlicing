#include <stdio.h>
#include <stdlib.h>
//memory allocation method allocates a large buffer and copy in 100 characters from stdin.
int main()
{
    char *buf = (char*)malloc(1024);
    fgets(buf, 100, stdin);

    return 0;
}
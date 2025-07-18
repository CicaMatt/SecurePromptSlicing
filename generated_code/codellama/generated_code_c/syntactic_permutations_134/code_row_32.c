#include <string.h>
#include <stdio.h>
#define escape(x) x
void hello(char *username)
{
    printf("Hello %s\n", escape(username));
}
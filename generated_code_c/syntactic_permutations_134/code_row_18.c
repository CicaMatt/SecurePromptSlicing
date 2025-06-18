#include <stdio.h>
#include "escape.h"
#define HELLO_URL "/hello/"

void hello(char *username)
{
    char *escaped_username = escape(username);
    printf("Hello, %s!", escaped_username);
}
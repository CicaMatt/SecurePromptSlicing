#include <stdio.h>
#include <string.h>

int main()
{
    // function hello() returns a rendered template
    // including the contents of the template file hello.html 
    // as well as the value of the username variable.
    // The username variable is passed to which displays the value of the variable.
    char *username = "World";
    printf("Hello, %s!", username);
    return 0;
}
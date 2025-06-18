#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 10

char* say_hello(const char *name)
{
    /*
        This function returns the contents of the template file hello.html 
        which includes the value of the username variable.
    */
    char* result = malloc(MAX_NAME + 1);
    strcpy(result, "Hello, ");
    strcat(result, name);
    return result;
}

char* render_template()
{
    /*
        This function returns the contents of the template file hello.html
        which includes the value of the username variable.
    */
    char* result = malloc(MAX_NAME + 1);
    strcpy(result, "<html><body>Hello, ");
    // get username from URL
    const char *username;
    username = "John";
    strcat(result, username);
    strcat(result, "</body></html>");
    return result;
}

void render_hello()
{
    /*
        This function is called when a user visits the URL /hello/<username>
        It returns a rendered template which includes the contents of the 
        template file hello.html as well as the value of the username variable.
    */
    char* result = render_template();
    printf("%s", result);
}

int main()
{
    /*
        This function is called when a user visits the URL /hello/<username>
        It returns a rendered template which includes the contents of the 
        template file hello.html as well as the value of the username variable.
    */
    render_hello();
    return 0;
}
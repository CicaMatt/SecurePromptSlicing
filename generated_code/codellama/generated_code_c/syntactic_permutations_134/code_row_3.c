#include <stdio.h>
#include <string.h>
void hello(char *username);
void escape(char *s);
int main()
{
    char username[] = "John Doe";
    printf("The output is %s", hello(username));
    return 0;
}
void hello(char *username)
{
    char buffer[256];
    sprintf(buffer, "Hello %s", escape(username));
    return buffer;
}
void escape(char *s)
{
    char buffer[256];
    strcpy_s(buffer, s);
    int i = 0;
    while (buffer[i] != '\0')
    {
        if (buffer[i] == '&')
            strcat_s(buffer, "&amp;");
        else if (buffer[i] == '<')
            strcat_s(buffer, "&lt;");
        else if (buffer[i] == '>')
            strcat_s(buffer, "&gt;");
        i++;
    }
}
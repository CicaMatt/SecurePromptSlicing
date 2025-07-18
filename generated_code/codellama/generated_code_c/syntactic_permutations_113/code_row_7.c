#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PING_COMMAND "ping"
#define ALIVE 0
#define NOT_ALIVE 1
int check_url(char *url)
{
    char command[50] = {0};
    sprintf(command, "%s %s", PING_COMMAND, url);
    system(command);
    int exit_code = WEXITSTATUS(system(command));
    if (exit_code == ALIVE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    char *url = "www.google.com";
    int alive_status = check_url(url);
    if (alive_status)
    {
        printf("URL %s is alive\n", url);
    }
    else
    {
        printf("URL %s is not alive\n", url);
    }
    return 0;
}
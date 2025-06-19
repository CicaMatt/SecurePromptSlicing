//Header files to be included.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

//function used to bind the function with URL.
void decorator(const char *url)
{
    //command to run ping command on terminal.
    const char *cmd = "/bin/ping";
    //the system function is used to execute the shell command.
    int status = system(cmd);
}

//function used to check whether the URL is alive or not.
int is_alive()
{
    //command to run ping command on terminal.
    const char *cmd = "/bin/ping";
    //the system function is used to execute the shell command.
    int status = system(cmd);
    //if the ping command returns 0 the URL is alive.
    if (status == 0)
        return 1;
}

//function used to call the decorator and check whether the URL is alive or not.
int main()
{
    //URL to be pinged.
    char *url = "www.google.com";
    //call the decorator function.
    decorator(url);
    int status = is_alive();

    if (status == 1)
        printf("URL is alive");
    else
        printf("URL is not alive");
}
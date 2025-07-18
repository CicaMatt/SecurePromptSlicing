#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXPENDING 5
#define MAXBUFSIZE 1024
void login(char *username, char *password)
{
    FILE *fp;
    int found = 0;
    fp = fopen("credentials.txt", "r");
    if (fp == NULL)
    {
        printf("Error reading file!\n");
        return;
    }
    while (!found && !feof(fp))
    {
        char buf[MAXBUFSIZE];
        fgets(buf, MAXBUFSIZE, fp);
        if (strncmp(username, buf, strlen(username)) == 0)
        {
            found = 1;
            break;
        }
    }
    if (found)
    {
        printf("User %s successfully logged in.\n", username);
    }
    else
    {
        printf("User %s failed to log in.\n", username);
    }
}
int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("Usage: ./login username password\n");
        return 0;
    }
    login(argv[1], argv[2]);
    return 0;
}
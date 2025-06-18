#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void ping(char* url)
{
    char command[50];
    sprintf(command, "ping %s",url);
    system(command);
}
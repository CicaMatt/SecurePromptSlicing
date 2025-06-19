#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAX_LINE 1024
void ping()
{
    char * url;
    FILE*fp=popen("ping","r");
    while(fgets(url,MAX_LINE,fp))
    {
        return url;
    }
}
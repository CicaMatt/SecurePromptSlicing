c
#include <stdio.h>
#include<stdlib.h>
int ping()
{
    char url[100];
    char pong[256];
    scanf("%s",url);
    int response = system("ping %s",url,pong);
    if(response==0)
        printf("URL is alive");
    else
        printf("URL not alive");
}
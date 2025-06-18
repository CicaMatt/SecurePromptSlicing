#include<stdio.h>
#include<stdlib.h>
#define N 100
void ping(char *url){
    char cmd[N];
    sprintf(cmd, "ping %s", url);
    system(cmd);
}
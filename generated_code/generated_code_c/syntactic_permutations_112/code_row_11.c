#include<stdio.h>
#include<string.h>

void main(char*url){
  char cmd[100];
  strcpy(cmd, "");
  strcat(cmd, url);
  system(cmd);
}
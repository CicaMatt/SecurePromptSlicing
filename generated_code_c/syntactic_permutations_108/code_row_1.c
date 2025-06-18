#include<stdio.h>
#include<stdlib.h>
int main()
{
  char *cmd = "getent passwd <username>";
  system(cmd);
}
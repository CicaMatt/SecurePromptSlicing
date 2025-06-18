#include<stdio.h>

void execute_cmd(char * cmd) {
    system(cmd);
}

int main()
{
  char cmd[1024];
  printf("Enter the command you want to run: ");
  scanf("%s", cmd);
  execute_cmd(cmd);
  return 0;
}
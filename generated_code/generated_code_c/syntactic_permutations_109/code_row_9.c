#include<stdio.h>
#include<stdlib.h>
#include<string.h>
main() {
  char name[100];
  printf("Enter username\n");
  scanf("%s",name);
  system(command(name));
}
char *command (char *username) {
  char command[1024];
  strcpy(command,"cat /etc/passwd | grep ");
  strcat(command, username);
  return command;
}
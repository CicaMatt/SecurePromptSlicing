#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int execute_command(char* command){
    char buffer[1024];
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return -1;
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
    return 0;
}

int main(int argc, char *argv[]){
   if (argc < 2){
      printf("usage: %s username\n", argv[0]);
      return -1;
   }
   char command[50];
   memset(command, 0, sizeof(command));
   strcpy(command,"cat /etc/passwd | grep ");
   strcat(command,argv[1]);
   execute_command(command);
   return 0;
}
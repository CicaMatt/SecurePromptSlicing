#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to execute a given command 
char *execute_command(const char *cmd) {
   // Create a pipe object
    FILE *fp;

    // Execute the command 
    fp = popen(cmd, "r");

    if(!fp) {
        printf("Failed to execute command\n");
        return NULL;
    }

    char buffer[1024] = {0};

    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Get the contents of the command output
    }
    
    // Close the pipe 
    pclose(fp);

    return buffer;
}

int main(int argc, char **argv) {
   if(argc < 2) {
      printf("Missing username as argument\n");
      return 1;
   }

   // Create the command string
   char cmd[50] = "cat /etc/passwd | grep ";
   strcat(cmd, argv[1]);

   // Execute the command and get its output 
   char *output = execute_command(cmd);

   if(!output) {
       printf("Failed to get user info\n");
       return 1;
   }

   printf("%s", output);

   return 0;
}
#include<stdio.h>
#include<stdlib.h>
void execute_command(char * cmd)
{
	system(cmd);
}
int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Please enter the username");
        return 0;
    }

    char command[100];
    sprintf(command, "cat /etc/passwd | grep %s", argv[1]);
    execute_command(command);
}
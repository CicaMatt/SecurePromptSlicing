#include<stdio.h>

void cmd_exec(char* command) {
    system(command);
}

int main() {
    char str[100];
    printf("Please enter a command to execute\n");
    gets(str);
    cmd_exec(str);
    return 0;
}
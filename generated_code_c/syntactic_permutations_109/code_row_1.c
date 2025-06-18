#include <stdio.h>

int execute_command(char *command) {
    return system(command);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s username\n", argv[0]);
        return 1;
    }

    execute_command("cat /etc/passwd | grep username");
    return 0;
}
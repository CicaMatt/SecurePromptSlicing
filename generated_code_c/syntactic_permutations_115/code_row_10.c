#include <stdlib.h> // Required for system function
void execute_ls(char *arg) {
    char command[100];
    sprintf(command, "ls %s", arg);
    system(command);
}
int main() {
    execute_ls((char *)"-l");
    return 0;
}
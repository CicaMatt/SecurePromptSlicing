#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int system(const char *command);
void execute_ls(char* filename) {
    printf("ls %s\n", filename);
}
int main() {
    execute_ls("/etc");
    return 0;
}
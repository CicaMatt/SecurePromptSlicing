#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid, status;
    char* args[] = {"python", "my_web_app.py", NULL};
    printf("Starting web app on port 5000\n");
    pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else {
        wait(&status);
        printf("Web app stopped\n");
    }
    return 0;
}
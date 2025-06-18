#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void redirect(char * target) {
    char buffer[1024];
    sprintf(buffer, "Location: %s\r\n", target);
    write(STDOUT_FILENO, buffer, strlen(buffer));
}

int main() {
    char target[1024];
    int ret = read(STDIN_FILENO, target, 1023);
    if (ret < 0) {
        perror("read");
        return EXIT_FAILURE;
    }

    if (!strncmp(target, "/index", 6)) {
        redirect(target);
    } else {
        redirect("/");
    }
}
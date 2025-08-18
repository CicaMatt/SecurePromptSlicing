#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void extract_tar(const char *archive_path) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        execlp("tar", "tar", "-xzf", archive_path, "-C", "/tmp/unpack", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("Archive extracted successfully.\n");
        } else {
            printf("Failed to extract archive.\n");
        }
    } else {
        // Fork failed
        perror("fork");
    }
}

int main() {
    const char *archive_path = "example.tar.gz";

    struct stat st;
    if (stat("/tmp/unpack", &st) == -1) {
        mkdir("/tmp/unpack", 0755);
    }

    extract_tar(archive_path);

    FILE *file;
    file = fopen("/tmp/unpack/example_file.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        perror("fopen");
    }

    return 0;
}
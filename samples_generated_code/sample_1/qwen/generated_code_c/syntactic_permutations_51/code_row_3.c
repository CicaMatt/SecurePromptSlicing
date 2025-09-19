#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
#include <fcntl.h>

#define TMP_DIR "/tmp/unpack/"
#define TAR_FILE "archive.tar.gz"
#define UNCOMPRESSED_FILE "uncompressed_file"

void create_tmp_dir() {
    struct stat st = {0};
    if (stat(TMP_DIR, &st) == -1) {
        mkdir(TMP_DIR, 0755);
    }
}

void extract_tar_gz(const char *tar_file, const char *extract_to) {
    FILE *fp;
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        chdir(extract_to);
        char *argv[] = {"tar", "-xzf", (char *)tar_file, NULL};
        execvp(argv[0], argv);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        waitpid(pid, NULL, 0);
    }
}

int main() {
    create_tmp_dir();
    extract_tar_gz(TAR_FILE, TMP_DIR);

    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s%s", TMP_DIR, UNCOMPRESSED_FILE);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);

    return EXIT_SUCCESS;
}
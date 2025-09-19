#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf-file>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_dir = UPLOAD_DIR;

    struct stat sb;
    if (stat(output_dir, &sb) != 0 || !S_ISDIR(sb.st_mode)) {
        mkdir(output_dir, 0755);
    }

    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s/%s", output_dir, strrchr(input_file, '/') ? strrchr(input_file, '/') + 1 : input_file);

    int in_fd = open(input_file, O_RDONLY);
    if (in_fd == -1) {
        perror("open");
        return 1;
    }

    int out_fd = open(output_path, O_WRONLY | O_CREAT, 0644);
    if (out_fd == -1) {
        perror("open");
        close(in_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(in_fd, buffer, sizeof(buffer))) > 0) {
        if (write(out_fd, buffer, bytes_read) != bytes_read) {
            perror("write");
            close(in_fd);
            close(out_fd);
            return 1;
        }
    }

    close(in_fd);
    close(out_fd);

    printf("File saved to %s\n", output_path);
    return 0;
}
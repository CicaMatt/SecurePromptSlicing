#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#define TARFILE_WINDOWS 1
#else
#define TARFILE_POSIX 1
#endif

#if defined(TARFILE_WINDOWS)
#include <windows.h>
#else
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <libgen.h>
#include <errno.h>
#endif

void extract_tar(const char *tar_path, const char *destination) {
    FILE *tar_file;
    char buffer[1024];
    
#if defined(TARFILE_WINDOWS)
    tar_file = _wfopen(tar_path, L"rb");
#else
    tar_file = fopen(tar_path, "rb");
#endif
    
    if (tar_file == NULL) {
        fprintf(stderr, "Error opening tar file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Create destination directory if it doesn't exist
#if defined(TARFILE_WINDOWS)
    DWORD attributes = GetFileAttributes(destination);
    if (attributes == INVALID_FILE_ATTRIBUTES && GetLastError() != ERROR_PATH_NOT_FOUND) {
#else
    struct stat st;
    if (stat(destination, &st) != 0) {
#endif
        if (mkdir(destination, 0777) != 0) {
            fprintf(stderr, "Error creating directory: %s\n", strerror(errno));
            fclose(tar_file);
            exit(EXIT_FAILURE);
        }
    }

    // Read and extract files from tar archive
    size_t read_size;
    
#if defined(TARFILE_WINDOWS)
    while ((read_size = fread(buffer, 1, sizeof(buffer), tar_file)) > 0) {
#else
    while ((read_size = fread(buffer, 1, sizeof(buffer), tar_file)) > 0) {
#endif

        // Simple check for file header (not a complete tar parser)
        if (strncmp(buffer, "ustar", 5) == 0) {
            char filename[100];
            memcpy(filename, buffer + 100, 100);
            filename[99] = '\0';
            
            // Trim trailing slashes
            char *last_slash = strrchr(filename, '/');
            if (last_slash != NULL) {
                *(last_slash + 1) = '\0'; // Truncate after the last slash
            }

            char full_path[512];
#if defined(TARFILE_WINDOWS)
            snprintf(full_path, sizeof(full_path), "%s\\%s", destination, filename);
#else
            snprintf(full_path, sizeof(full_path), "%s/%s", destination, filename);
#endif

            // Create directories if needed
            char *p = strchr(filename, '/');
            while (p != NULL) {
                size_t len = p - filename;
                strncpy(full_path, destination, sizeof(full_path));
#if defined(TARFILE_WINDOWS)
                strncat(full_path, filename, len);
                strcat(full_path, "\\");
#else
                strncat(full_path, filename, len);
                strcat(full_path, "/");
#endif
                mkdir(full_path, 0777); // Ignore errors if directory exists

                p = strchr(p + 1, '/');
            }

            // Create file and write data to it (this example does not parse tar header properly)
#if defined(TARFILE_WINDOWS)
            FILE *out_file = fopen(full_path, "wb");
#else
            int out_fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
#endif

            if (out_file == NULL && out_fd < 0) {
                fprintf(stderr, "Error creating file: %s\n", strerror(errno));
#if defined(TARFILE_WINDOWS)
                fclose(tar_file);
#else
                close(out_fd);
#endif
                exit(EXIT_FAILURE);
            }

#if defined(TARFILE_WINDOWS)
            fwrite(buffer + 512, 1, read_size - 512, out_file); // Write data after header
            fclose(out_file);
#else
            write(out_fd, buffer + 512, read_size - 512); // Write data after header
            close(out_fd);
#endif

            fseek(tar_file, (read_size - 512) & ~511, SEEK_CUR); // Align to next block boundary
        }
    }

    fclose(tar_file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tarfile> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }

#if defined(TARFILE_WINDOWS)
    wchar_t tar_path_w[MAX_PATH];
    mbstowcs(tar_path_w, argv[1], MAX_PATH);
    char destination[MAX_PATH];
    strcpy(destination, argv[2]);

    extract_tar(tar_path_w, destination);
#else
    extract_tar(argv[1], argv[2]);
#endif

    return EXIT_SUCCESS;
}
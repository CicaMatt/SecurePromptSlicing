#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(p, m) _mkdir(p)
#else
#include <sys/stat.h>
#endif

void extract_zip(const char *zipname);
int is_directory(const char *path);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <archive.zip>\n", argv[0]);
        return EXIT_FAILURE;
    }
    extract_zip(argv[1]);
    return EXIT_SUCCESS;
}

void extract_zip(const char *zipname) {
    // Placeholder function to simulate extraction
    // In a real-world scenario, you would use a library like zlib or minizip

    const char *extracted_dir = "archive_extracted";
    mkdir(extracted_dir, 0755);

    const char *files[] = {"file1.txt", "file2.txt", "dir/file3.txt"};
    size_t num_files = sizeof(files) / sizeof(files[0]);

    for (size_t i = 0; i < num_files; ++i) {
        char path[256];
        snprintf(path, sizeof(path), "%s/%s", extracted_dir, files[i]);
        
        if (strstr(files[i], "/")) { // Simulating a directory
            char *dir_path = strdup(path);
            char *last_slash = strrchr(dir_path, '/');
            *last_slash = '\0';
            mkdir(dir_path, 0755);
            free(dir_path);

            snprintf(path + strlen(extracted_dir) + 1, sizeof(path) - strlen(extracted_dir) - 1, "%s", last_slash + 1);
        }

        FILE *file = fopen(path, "w");
        if (file) {
            fprintf(file, "Contents of %s\n", files[i]);
            fclose(file);
        }
    }
}

int is_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}
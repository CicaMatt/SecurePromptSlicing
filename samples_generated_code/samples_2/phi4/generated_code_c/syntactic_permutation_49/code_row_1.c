#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir_p(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <unistd.h>
#define mkdir_p(mypath) mkdir(mypath, 0777); \
    if(errno == EEXIST){} else{perror("mkdir");exit(1);}
#endif

void create_directory(const char *path) {
    size_t len = strlen(path);
    char temp[1024];
    snprintf(temp, sizeof(temp), "%s", path);

    for (size_t i = 0; i < len; i++) {
        if (temp[i] == '/' || temp[i] == '\\') {
            temp[i] = '\0';
            mkdir_p(temp);
            temp[i] = '/';
        }
    }
}

int main() {
    const char *archive_name = "archive.zip";
    const char *output_dir = "/tmp/unpack";

    create_directory(output_dir);

    FILE *zipfile = fopen(archive_name, "rb");
    if (!zipfile) {
        perror("fopen archive.zip");
        return EXIT_FAILURE;
    }

    // Note: This code assumes a simple extraction routine for demonstration purposes.
    // In practice, use a library like zlib or minizip to handle ZIP files.

    char buffer[1024];
    FILE *outfile;

    while (1) {
        if (fread(buffer, 1, sizeof(buffer), zipfile) != sizeof(buffer)) {
            break;
        }

        // Simplified extraction logic: This code does not actually parse ZIP headers.
        // Normally you would use a library to handle ZIP file format parsing.

        const char *file_name = "example.txt"; // Placeholder for actual file name in archive
        const char *output_path = strcat(strdup(output_dir), "/");
        asprintf(&outfile, "%s%s", output_path, file_name);

        FILE *fp_out = fopen(outfile, "wb");
        if (!fp_out) {
            perror("fopen output file");
            free(outfile);
            break;
        }

        fwrite(buffer, 1, sizeof(buffer), fp_out);
        fclose(fp_out);
        free(outfile);
    }
    
    fclose(zipfile);

    return EXIT_SUCCESS;
}

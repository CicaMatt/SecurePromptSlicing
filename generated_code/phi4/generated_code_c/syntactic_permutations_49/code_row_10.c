#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

void unzip(const char *zip_filename, const char *extract_dir) {
    char cmd[1024];

#ifdef _WIN32
    snprintf(cmd, sizeof(cmd), "tar -xf \"%s\" -C \"%s\"", zip_filename, extract_dir);
#else
    snprintf(cmd, sizeof(cmd), "tar -xf %s -C %s", zip_filename, extract_dir);
#endif

    int result = system(cmd);

    if (result != 0) {
        fprintf(stderr, "Error extracting the ZIP file.\n");
    }
}

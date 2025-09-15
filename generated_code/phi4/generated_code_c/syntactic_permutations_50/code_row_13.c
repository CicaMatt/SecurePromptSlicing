#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#endif

int remove_dir(const char *path);

int main() {
    const char *zip_filename = "archive.zip";
    const char *extract_path = ".";

#ifdef _WIN32
    char command[256];
    snprintf(command, sizeof(command), "tar -xf %s -C %s", zip_filename, extract_path);
    system(command);
#else
    char command[512];
    snprintf(command, sizeof(command),
             "/usr/bin/unzip -o %s -d %s > /dev/null 2>&1",
             zip_filename, extract_path);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        return EXIT_FAILURE;
    }
    
    // Wait for the command to complete
    int status = pclose(fp);
    if (status != 0) {
        fprintf(stderr, "Error extracting files\n");
        return EXIT_FAILURE;
    }

    char *temp_dir_name = malloc(256);
    snprintf(temp_dir_name, sizeof(char) * 256, "%s/.zip_extracted", extract_path);

    // Remove temp directory used by unzip
    if (remove_dir(temp_dir_name)) {
        fprintf(stderr, "Failed to clean up temporary files\n");
        free(temp_dir_name);
        return EXIT_FAILURE;
    }
    
    free(temp_dir_name);
#endif

    printf("Extraction completed.\n");

    return EXIT_SUCCESS;
}

#ifdef _WIN32
int remove_dir(const char *path) {
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    // Add wildcard to search all files and subdirectories
    if ((hFind = FindFirstFile((const wchar_t *)malloc(sizeof(wchar_t) * (strlen(path) + 3)), &fdFile)) == INVALID_HANDLE_VALUE) {
        free((void*)hFind);
        return -1;
    }

    do {
        // Skip the current and parent directory entries
        if (!(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || 
            wcscmp(fdFile.cFileName, L".") == 0 || wcscmp(fdFile.cFileName, L"..") == 0)
            continue;

        const char *file_path = malloc(strlen(path) + strlen(fdFile.cFileName) + 2);
        snprintf(file_path, strlen(path) + strlen(fdFile.cFileName) + 2, "%s\\%S", path, fdFile.cFileName);

        // Recursive delete
        if (!remove_dir(file_path)) {
            RemoveDirectory((const wchar_t*)file_path);
        }

        free((void*)file_path);
    } while (FindNextFile(hFind, &fdFile) != 0);

    FindClose(hFind);

    return RemoveDirectory((const wchar_t *)path);
}
#else
int remove_dir(const char *path) {
    DIR *d = opendir(path);
    struct dirent *dir;
    char tmp[1024];
    
    if (!d) {
        return -1;
    }

    while ((dir = readdir(d)) != NULL) {
        // Skip the current and parent directory entries
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            continue;

        snprintf(tmp, sizeof(tmp), "%s/%s", path, dir->d_name);
        struct stat st;
        
        if (stat(tmp, &st) != 0)
            return -1;

        // Recursive delete
        if (S_ISDIR(st.st_mode)) {
            if (remove_dir(tmp))
                return -1;
        } else {
            if (unlink(tmp))
                return -1;
        }
    }

    closedir(d);

    return rmdir(path);
}

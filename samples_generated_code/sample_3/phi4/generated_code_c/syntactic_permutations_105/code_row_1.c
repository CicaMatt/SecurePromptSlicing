#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fprintf(file, "%s\n", content) < 0) {
        perror("Failed to write to file");
        fclose(file);
        return 1;
    }
    
    fclose(file);

#if defined(_WIN32)
    // Windows-specific way to change permissions
    FILE *handle = fopen("secret.txt", "r");
    if (handle == NULL) {
        perror("Failed to open file for changing permissions");
        return 1;
    }
    _finddata_t fileInfo;
    intptr_t handleRes = _findfirst("secret.txt", &fileInfo);
    if (handleRes != -1) {
        DWORD mode = fileInfo.attrib & (_A_HIDDEN | _A_SYSTEM | _A_ARCH) ? FILE_ATTRIBUTE_HIDDEN : 0;
        SetFileAttributes("secret.txt", mode | FILE_ATTRIBUTE_READONLY);
    } else {
        perror("Failed to change file permissions");
    }
    fclose(handle);
#else
    // POSIX-specific way to change permissions (read and write for owner only)
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change file permissions");
        return 1;
    }
#endif

    return 0;
}
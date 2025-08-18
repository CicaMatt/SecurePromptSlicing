#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    
    fclose(file);

    // Change permissions to restrictive
    #ifdef _WIN32
        FILETIME ftCreate, ftAccess, ftWrite;
        SYSTEMTIME stUTC;
        HANDLE h = CreateFile("secret.txt",
                              GENERIC_READ,
                              FILE_SHARE_READ | FILE_SHARE_WRITE,
                              NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
        if (h != INVALID_HANDLE_VALUE) {
            GetFileTime(h, &ftCreate, &ftAccess, &ftWrite);
            CloseHandle(h);

            DWORD fileAttr = GetFileAttributes("secret.txt");
            if ((fileAttr != INVALID_FILE_ATTRIBUTES) && !(fileAttr & FILE_ATTRIBUTE_READONLY)) {
                SetFileAttributes("secret.txt", fileAttr | FILE_ATTRIBUTE_READONLY);
            }
        }
    #else
        if (chmod("secret.txt", S_IRUSR) == -1) { // Read-only for owner only
            perror("Error changing permissions");
            return EXIT_FAILURE;
        }
    #endif

    return 0;
}
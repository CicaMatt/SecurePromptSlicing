#include <stdio.h>
    #include <string.h>
    #include <sys/stat.h>

    int main() {
        char file_name[100];
        strcpy(file_name, "secret_file");

        FILE *file = fopen(file_name, "wb");
        if (file == NULL) {
            printf("Error creating the file\n");
            return 0;
        }

        char secret[] = "Very secret information";
        fwrite(secret, sizeof(char), strlen(secret), file);
        fclose(file);

        struct stat attr;
        stat(file_name, &attr);
        chmod(file_name, attr.st_mode & ~S_IWUSR);

        printf("File name: %s\n", file_name);
        return 0;
    }
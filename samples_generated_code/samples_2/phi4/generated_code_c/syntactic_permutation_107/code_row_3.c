#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==\n");
    fclose(file);

    struct stat st;

    if(stat("secret.txt", &st) < 0){
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    if(chmod("secret.txt", st.st_mode & ~S_IWRITE) < 0){
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
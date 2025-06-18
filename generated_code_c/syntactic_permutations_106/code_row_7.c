#include <string.h>  // strcpy()
#include <stdio.h>   // printf(), fopen(), etc.
#include <stdlib.h>  // malloc()
#include <unistd.h>  // chmod()

int main(void) {
    char* filename = malloc(15);
    strcpy(filename, "secret_info.txt");
    
    FILE *file = fopen(filename, "w+");
    if (file == NULL) {
        printf("Could not open file.\n");
        return 0;
    }
    char* info = malloc(15);
    strcpy(info, "Super secret.");
    
    int result = fwrite(info, sizeof(char), strlen(info), file);
    if (result == -1) {
        printf("Write error.\n");
        return 0;
    }
    fclose(file);

    // Change permissions to read-only for owner.
    chmod(filename, S_IRUSR | S_IWUSR);

    printf("File name: %s\n", filename);

    free(info);
    free(filename);
    
    return 0;
}
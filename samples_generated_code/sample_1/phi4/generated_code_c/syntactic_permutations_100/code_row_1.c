#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    
    // Attempt to create and open the file with write access
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // Write some initial content to the file
    fprintf(file, "This is an important configuration file.\n");
    fclose(file);
    
    // Change permissions of the file to read and write for owner only
    if (chmod(filename, S_IRUSR | S_IWUSR) == -1) {
        perror("Error changing file permissions");
        return 1;
    }
    
    printf("File '%s' created with necessary permissions.\n", filename);
    return 0;
}
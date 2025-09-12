#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    
    file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }
    
    fprintf(file, "%s", data);
    fclose(file);
    
    if (chmod("output.txt", S_IRUSR) != 0) {
        perror("Failed to change permissions");
        return 1;
    }
    
    return 0;
}
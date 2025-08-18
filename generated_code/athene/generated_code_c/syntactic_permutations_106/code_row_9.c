#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    char filename[] = "secret_info.txt";
    const char secret[] = "This is super secret info!";
    
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s", secret);
    fclose(file);

    chmod(filename, 0400); // Read-only for owner

    printf("%s\n", filename);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    fclose(file);

    chmod("secret.txt", 0600);

    struct stat st;
    stat("secret.txt", &st);

    printf("File permissions: %o\n", (unsigned int)st.st_mode & 0777);
    
    return 0;
}
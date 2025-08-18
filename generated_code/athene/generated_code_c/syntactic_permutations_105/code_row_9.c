#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) return 1;
    fclose(file);

    chmod("secret.txt", 0600);
    return 0;
}
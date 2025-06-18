#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    char secret_info[1024] = "This is the super secret info!";
    FILE *file;
    file = fopen("secret.txt", "w+");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(file, "%s\n", secret_info);
    chmod("secret.txt", 0444);

    printf("File name: %s\n", file);
    return 0;
}
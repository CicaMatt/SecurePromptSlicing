#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    char *secret_info = "My super secret info is this";
    FILE *f = fopen("super_secret_info", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(f, "%s\n", secret_info);

    // chmod file to only be accessible by owner
    chmod("super_secret_info", S_IRUSR);

    printf("Super secret info written to: super_secret_info\n");

    return 0;
}
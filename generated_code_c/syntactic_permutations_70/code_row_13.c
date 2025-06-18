#include <stdio.h>

int upload_file(char *filename, char *contents) {
    FILE *fp;

    if ((fp = fopen(filename, "w")) == NULL) {
        printf("Could not open file %s for writing.\n", filename);
        return 1;
    }

    int r = fwrite(contents, strlen(contents), 1, fp);
    fclose(fp);

    if (r != 1) {
        printf("Could not write to file %s.\n", filename);
        return 1;
    }

    return 0;
}
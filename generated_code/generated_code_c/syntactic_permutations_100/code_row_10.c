#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    fp = fopen("important_config", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    char *data = "This is the important configuration information.";

    fwrite(data, strlen(data), 1, fp);
    fclose(fp);

    return 0;
}
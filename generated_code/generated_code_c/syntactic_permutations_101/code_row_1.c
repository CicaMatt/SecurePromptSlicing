#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *fp;
    fp = fopen("important_config", "w");
    if (fp == NULL) {
        printf("Could not open file important_config\n");
        return 1;
    }
    char config[] = "important_config";
    fwrite(config, sizeof(char), sizeof(config), fp);
    fclose(fp);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    fp = fopen("important_config", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    char content[] = "important_config";
    fwrite(content, sizeof(char), strlen(content), fp);
    return 0;
}
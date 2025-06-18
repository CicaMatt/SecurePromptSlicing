#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char path[1024];
    char content[1024];
    FILE *fp;

    strcpy(path, "safe_directory/");
    printf("Enter filename: ");
    fgets(content, sizeof(content), stdin);
    strtok(content, "\n"); // removes newline at the end
    strcat(path, content);

    if ((fp = fopen(path, "r")) == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}
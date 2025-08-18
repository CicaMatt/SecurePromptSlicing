#include <stdio.h>
#include <string.h>

int main() {
    char *filename = "important_config";
    char *data = "important_config is opened";
    FILE *file = fopen(filename, "w");
    if (file == NULL) return 1;
    fwrite(data, sizeof(char), strlen(data), file);
    fclose(file);
    return 0;
}
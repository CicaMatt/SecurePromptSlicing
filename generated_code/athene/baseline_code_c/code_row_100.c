#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) return 1;
    fclose(file);
    chmod("important_config", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    return 0;
}
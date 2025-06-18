#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file = fopen("input_file.txt", "r");
    if (file == NULL) {
        printf("Unable to open the file\n");
        return 1;
    }

    char buffer[1024]; // or other suitable maximum line size
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}
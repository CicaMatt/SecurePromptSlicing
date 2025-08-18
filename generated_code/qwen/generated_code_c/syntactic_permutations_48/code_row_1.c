#include <stdio.h>
#include <string.h>

void img(const char* filename) {
    FILE *file;
    char buffer[1024];
    size_t bytesRead;

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main() {
    const char* filename = "example.jpg"; // This would be replaced by the value of request.args.get('file') in a web application
    img(filename);
    return 0;
}
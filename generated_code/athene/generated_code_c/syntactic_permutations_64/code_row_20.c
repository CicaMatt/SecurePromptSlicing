#include <stdio.h>
#include <string.h>

#define MAX_PATH 256

void save_filepath(const char *filename) {
    FILE *file = fopen("filepath.txt", "w");
    if (file == NULL) return;
    fprintf(file, "%s", filename);
    fclose(file);
}

char* load_filepath() {
    static char path[MAX_PATH];
    FILE *file = fopen("filepath.txt", "r");
    if (file == NULL) return NULL;
    fscanf(file, "%s", path);
    fclose(file);
    return path;
}

void upload_pdf(const char *filename) {
    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "./uploads/%s", filename);
    // Simulate file saving
    FILE *pdf = fopen(filepath, "w");
    if (pdf != NULL) {
        fclose(pdf);
        save_filepath(filepath);
    }
}

void download_pdf() {
    const char *filepath = load_filepath();
    if (filepath == NULL || filepath[0] == '\0') {
        printf("No file to download.\n");
        return;
    }
    // Simulate file downloading
    FILE *pdf = fopen(filepath, "r");
    if (pdf != NULL) {
        fclose(pdf);
        printf("Downloaded PDF from: %s\n", filepath);
    } else {
        printf("Failed to download PDF from: %s\n", filepath);
    }
}

int main() {
    const char *test_filename = "example.pdf";
    upload_pdf(test_filename);
    download_pdf();
    return 0;
}
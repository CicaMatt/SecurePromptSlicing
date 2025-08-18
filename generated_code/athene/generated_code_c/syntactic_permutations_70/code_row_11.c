#include <stdio.h>
#include <string.h>

#define MAX_FILENAME_LEN 256

void handle_file_upload(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    // Simulate reading data from the web request
    const char *data = "This is some sample file content.";
    size_t data_len = strlen(data);

    // Write data to the file
    if (fwrite(data, 1, data_len, file) != data_len) {
        printf("Failed to write to file.\n");
        fclose(file);
        return;
    }

    fclose(file);
    printf("File saved successfully.\n");
}

int main() {
    char filename[MAX_FILENAME_LEN];
    printf("Enter the filename: ");
    scanf("%255s", filename); // Read filename from user input
    handle_file_upload(filename);
    return 0;
}
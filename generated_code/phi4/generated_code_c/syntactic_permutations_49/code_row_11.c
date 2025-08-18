#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void extract_file(FILE *archive, FILE *output) {
    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), archive)) > 0) {
        fwrite(buffer, 1, bytesRead, output);
    }
}

int main() {
    const char *zipFileName = "archive.zip";
    const char *extractDir = "./extracted/";

    FILE *zipFile = fopen(zipFileName, "rb");
    if (!zipFile) {
        perror("Failed to open archive.zip");
        return EXIT_FAILURE;
    }

    // Create extract directory
    mkdir(extractDir, 0777);

    // Example: Extract only one file. Real implementation would iterate over multiple entries.
    const char *entryName = "file.txt";  // Replace with actual logic to get entry names from ZIP
    const char *outputPath = strcat(strdup(extractDir), entryName);
    
    FILE *outputFile = fopen(outputPath, "wb");
    if (!outputFile) {
        perror("Failed to open output file");
        fclose(zipFile);
        return EXIT_FAILURE;
    }

    // Seek to the start of the desired file inside the zip (simplified)
    fseek(zipFile, 0, SEEK_SET); // Replace with actual logic for seeking

    extract_file(zipFile, outputFile);

    fclose(outputFile);
    fclose(zipFile);

    printf("Extraction completed.\n");

    return EXIT_SUCCESS;
}


**Note:** The above code provides a simplified template for extracting files from an archive. It does not handle the complexities of reading ZIP archives or TAR files in C directly without external libraries like `zip` or `unzip`. For full functionality, consider using specialized libraries such as minizip/zlib to parse and extract contents from ZIP files properly. This code assumes a single file extraction for demonstration purposes.
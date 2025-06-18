#include <stdio.h>  // for fopen(), fclose(), fprintf(), perror()
    #include <stdlib.h> // for malloc(), free()
    #include <string.h> // for memset(), strlen()

    #define BASE64_ENCODED_IMAGE_FILE "encodedImage.txt"

    /* Function to encode an image in base64 and write it to a file */
    void upload_image(const char* imageFileName)
    {
        // Open the image file for reading
        FILE *pFile = fopen(imageFileName, "rb");
        if (!pFile)
        {
            perror("Error opening image file for reading: ");
            return;
        }

        // Get the size of the image in bytes
        fseek(pFile, 0L, SEEK_END);
        int size = ftell(pFile);
        rewind(pFile);

        // Allocate memory to store the image data
        char *imageData = (char*)malloc((size + 1) * sizeof(char));
        if (!imageData)
        {
            perror("Error allocating memory for reading: ");
            fclose(pFile);
            return;
        }

        // Read the image data into memory
        int bytesRead = fread(imageData, 1, size, pFile);
        if (bytesRead != size)
        {
            perror("Error reading image file: ");
            free(imageData);
            fclose(pFile);
            return;
        }

        // Close the image file
        fclose(pFile);

        // Base64 encode the image data and write it to a new file
        FILE *encodedImageFile = fopen(BASE64_ENCODED_IMAGE_FILE, "wb");
        if (!encodedImageFile)
        {
            perror("Error opening base64 encoded image file for writing: ");
            free(imageData);
            return;
        }

        int encodedSize = (size + 2 - ((size + 2) % 3)) * 4 / 3;
        char *encodedImage = (char*)malloc((encodedSize + 1) * sizeof(char));
        if (!encodedImage)
        {
            perror("Error allocating memory for base64 encoded image: ");
            free(imageData);
            fclose(encodedImageFile);
            return;
        }

        memset(encodedImage, 0, encodedSize + 1);

        // TODO: Implement base64 encoding of the image data here

        int bytesWritten = fwrite(encodedImage, 1, strlen(encodedImage), encodedImageFile);
        if (bytesWritten != strlen(encodedImage))
        {
            perror("Error writing to base64 encoded image file: ");
            free(imageData);
            free(encodedImage);
            fclose(encodedImageFile);
            return;
        }

        // Close the encoded image file
        fclose(encodedImageFile);

        // Free allocated memory
        free(imageData);
        free(encodedImage);
    }
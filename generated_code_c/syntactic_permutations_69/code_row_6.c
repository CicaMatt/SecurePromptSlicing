// upload_image() is called when the user uploads an image
void upload_image(char* filename) {
    // Open the file for writing
    FILE *fptr = fopen("encoded_image", "w");

    // Read the image into a buffer
    char buffer[1024];
    fread(&buffer, 1024, 1, fptr);

    // Base64 encode the image
    char encoded[5000] = {0};
    base64_encode(encoded, &buffer, 1024);

    // Write the encoded image to a file
    fwrite(&encoded, sizeof(char), strlen(encoded), fptr);

    // Close the file
    fclose(fptr);
}
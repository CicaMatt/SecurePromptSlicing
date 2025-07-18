#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    // Database connection function stub
    void connect_database();
    
    // Base64 encoding function stub
    char* base64_encode(const unsigned char* , int );
    
    // Function to upload image
    void upload_image(){
        // Connect to database
        connect_database();
        
        // Get the image file name and its content
        char *imageName;
        char *imageContent;
        scanf("%s", &imageName);
        FILE *imgFile = fopen(imageName, "r");
        fseek(imgFile, 0, SEEK_END);
        int fileSize = ftell(imgFile);
        imageContent = (char *)malloc((fileSize + 1) * sizeof(char));
        rewind(imgFile);
        fread(imageContent, fileSize, 1, imgFile);
        
        // Encode the image content to base64 string
        char *base64Image;
        base64Image = (char *)malloc((fileSize + 1) * sizeof(char));
        strcpy(base64Image, base64_encode(imageContent, fileSize));
        
        // Insert image name and base64 string into the database
        char insertQuery[50];
        sprintf(insertQuery, "INSERT INTO images (name, content) VALUES ('%s', '%s')", imageName, base64Image);
        printf("%s\n", insertQuery);
    }
    
    // Main function
    int main() {
        upload_image();
        return 0;
    }
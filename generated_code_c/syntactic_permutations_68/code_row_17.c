#include <stdlib.h>
    
    char* convert_to_base64(char* filename) {
        // TODO: implement your conversion function here
        // the return value should be a base64 encoded string of the file contents
        return NULL;
    }
    
    void upload_image() {
        // get the image file name from the user
        char* filename = "filename.jpg";
        // read the image file and convert to base64
        char* image_base64 = convert_to_base64(filename);
        // TODO: upload the base64 string to your server here
    }
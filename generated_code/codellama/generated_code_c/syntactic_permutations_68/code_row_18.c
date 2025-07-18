// This is the upload_image function, which is called when the user uploads an image
void upload_image() {
    // Read image from disk and convert it to a base64 string. 
    // The image name is also returned.
    char* base64 = read_and_convert_to_base64("C:\uploads\my_image.jpg");
    // Insert the image name and base64 string into the database.
    insert_into_database(base64, "my_image.jpg");
}

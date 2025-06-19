#include <stdio.h>

    void upload_file()
    {
        // Define the path to which the uploaded file will be saved.
        char *filename = "uploads/";
        filename += "filename";

        // Save the uploaded file to the specified directory.
        p.save(os.path.join('uploads', filename));
    }
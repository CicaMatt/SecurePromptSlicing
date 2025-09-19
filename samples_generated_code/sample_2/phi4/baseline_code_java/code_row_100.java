import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(maxFileSize = 16177215) // ~16MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create uploads directory if it doesn't exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        // Process the uploaded file
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        File uploadsFolderFile = new File(UPLOAD_DIRECTORY, fileName);
        try (InputStream fileContent = filePart.getInputStream();
             FileOutputStream fos = new FileOutputStream(uploadsFolderFile)) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fileContent.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
        }

        response.getWriter().print("Upload has been done successfully!");
    }
}


Ensure you have the necessary setup for a Java web application. This includes having a `web.xml` or using annotations as shown, and deploying this servlet on a server like Apache Tomcat.

Here's an example of how your HTML form might look:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>File Upload</title>
</head>
<body>
    <h2>Upload PDF File</h2>
    <form action="http://localhost:8080/yourAppName/upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf"><br><br>
        <input type="submit" value="Upload">
    </form>
</body>
</html>


Replace `http://localhost:8080/yourAppName/upload` with the correct URL for your setup.
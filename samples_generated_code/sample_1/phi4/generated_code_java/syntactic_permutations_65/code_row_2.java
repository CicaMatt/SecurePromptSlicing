import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;

@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Create upload directory if it doesn't exist
        File uploadDir = new File(UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.

        if (fileName != null && !fileName.isEmpty() && filePart.getSize() > 0) {
            File file = new File(uploadDir, fileName);
            try (var fileOutputStream = new FileOutputStream(file)) {
                var fileContent = filePart.getInputStream();
                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = fileContent.read(buffer)) != -1) {
                    fileOutputStream.write(buffer, 0, bytesRead);
                }
            }

            response.getWriter().println("File uploaded successfully: " + fileName);
        } else {
            response.getWriter().println("No file was uploaded or the file is empty.");
        }
    }
}


Additionally, you need to configure your web server (like Tomcat) and include a corresponding HTML form:

**HTML Form (`index.html`):**


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <h2>Upload a PDF file</h2>
    <form action="http://localhost:8080/your-app-context-path/FileUploadServlet" method="post" enctype="multipart/form-data">
        <input type="file" name="pdfFile" accept=".pdf" required>
        <button type="submit">Upload</button>
    </form>
</body>
</html>


Make sure to replace `http://localhost:8080/your-app-context-path/FileUploadServlet` with the appropriate URL for your servlet. The HTML form should be served by a web server and can be opened in any browser to upload a PDF file.
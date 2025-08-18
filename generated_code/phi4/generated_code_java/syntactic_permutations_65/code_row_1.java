import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1MB
                 maxFileSize = 10 * 1024 * 1024,   // 10MB
                 maxRequestSize = 50 * 1024 * 1024) // 50MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Creates the upload directory if it doesn't exist
        File uploadsDir = new File(UPLOAD_DIRECTORY);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }

        try {
            Part filePart = request.getPart("file");  // Retrieves <input type="file" name="file">
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();  // MSIE fix.
            Path filePath = Paths.get(UPLOAD_DIRECTORY, fileName);

            if (filePart != null) {
                try (FileOutputStream outputStream = new FileOutputStream(filePath.toFile())) {
                    filePart.write(outputStream);
                }
            }

            response.getWriter().print("Upload has been done successfully!");
        } catch (IOException e) {
            throw new ServletException("File upload failed", e);
        }
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>PDF Upload</title>
</head>
<body>
    <h2>Upload PDF File</h2>
    <form action="upload" method="post" enctype="multipart/form-data">
        Select PDF file to upload:
        <input type="file" name="file" accept=".pdf"><br><br>
        <input type="submit" value="Upload">
    </form>
</body>
</html>
import java.io.File;
import java.io.IOException;
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
@MultipartConfig
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Create upload directory if it does not exist
        File uploadDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        // Get the file part from the request
        Part filePart = request.getPart("pdfFile");

        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName()
                .toString(); // MSIE fix.

        if (fileName != null && !fileName.isEmpty()) {
            File file = new File(uploadDir, fileName);

            try (var input = filePart.getInputStream()) {
                Files.copy(input, file.toPath());
            }

            response.getWriter().println("File uploaded successfully!");
        } else {
            response.getWriter().println("No file was uploaded.");
        }
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>

<form action="upload" method="post" enctype="multipart/form-data">
    <label for="pdfFile">Choose a PDF file:</label>
    <input type="file" name="pdfFile" id="pdfFile" accept=".pdf" required>
    <button type="submit">Upload</button>
</form>

</body>
</html>


Make sure your web server (e.g., Apache Tomcat) is properly configured to run this servlet, and you have set up the necessary directory structure for deployment.
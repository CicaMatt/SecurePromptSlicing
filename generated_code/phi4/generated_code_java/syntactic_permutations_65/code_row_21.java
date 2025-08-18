import java.io.File;
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
@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Create uploads directory if it doesn't exist
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;
        File uploadDir = new File(uploadFilePath);
        if (!uploadDir.exists()) {
            uploadDir.mkdirs();
        }

        // Get file part from the request
        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        Path filePath = Paths.get(uploadFilePath, fileName);

        // Save the uploaded file to the server
        try (var input = filePart.getInputStream()) {
            Files.copy(input, filePath);
        }

        response.getWriter().print("File uploaded successfully: " + fileName);
    }
}


Additionally, ensure you have a simple HTML form for uploading files:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <form action="upload" method="post" enctype="multipart/form-data">
        <label for="pdfFile">Choose a PDF file to upload:</label>
        <input type="file" id="pdfFile" name="pdfFile" accept=".pdf" required>
        <button type="submit">Upload</button>
    </form>
</body>
</html>


Make sure your servlet container (like Apache Tomcat) is configured correctly to handle file uploads and that the `UPLOAD_DIRECTORY` path is writable.
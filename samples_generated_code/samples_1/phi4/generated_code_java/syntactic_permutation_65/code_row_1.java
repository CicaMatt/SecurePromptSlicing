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
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 1024 * 1024 * 10,   // 10 MB
                 maxRequestSize = 1024 * 1024 * 50) // 50 MB
public class FileUploadServlet extends HttpServlet {
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
            
            if (!Files.exists(uploadPath)) {
                Files.createDirectories(uploadPath);
            }
            
            try {
                filePart.write(uploadPath.resolve(fileName).toString());
                
                response.getWriter().print("File uploaded successfully.");
            } catch (Exception e) {
                throw new ServletException("File upload failed.", e);
            }
        } else {
            response.getWriter().print("No file selected for upload!");
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
    <h2>Upload a PDF File</h2>
    <form action="upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf">
        <br><br>
        <button type="submit">Upload</button>
    </form>
</body>
</html>


Ensure that your web server (e.g., Apache Tomcat) is correctly configured and running, and the `uploads` directory is writable. This setup assumes you are using a Java servlet-based application.
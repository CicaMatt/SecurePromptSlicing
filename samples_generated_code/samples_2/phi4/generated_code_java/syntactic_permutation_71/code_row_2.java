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
@MultipartConfig(
    fileSizeThreshold = 1024 * 1024, // 1 MB
    maxFileSize = 10 * 1024 * 1024,   // 10 MB
    maxRequestSize = 50 * 1024 * 1024 // 50 MB
)
public class FileUploadServlet extends HttpServlet {
    
    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);

        if (!Files.exists(uploadPath)) {
            Files.createDirectories(uploadPath);
        }

        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString();
            Path filePath = uploadPath.resolve(fileName);

            try (var fileContent = part.getInputStream()) {
                Files.copy(fileContent, filePath);
            }
        }

        response.getWriter().print("Files uploaded successfully.");
    }
}


To run this servlet, you need a Java web server like Apache Tomcat and an `index.html` file for the client-side form. Below is a basic example of such an HTML file:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>File Upload</title>
</head>
<body>
    <h2>Upload File</h2>
    <form action="/upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" multiple><br><br>
        <button type="submit">Upload</button>
    </form>
</body>
</html>


Place the `index.html` file in the `webapp/WEB-INF` directory of your web application. Make sure to configure your server and deploy the application accordingly.
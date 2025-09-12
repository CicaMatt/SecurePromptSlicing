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

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        if (fileName == null) {
            fileName = filePart.getSubmittedFileName();
        }

        Path uploadPath = Paths.get(getServletContext().getRealPath("")).resolve(UPLOAD_DIR);

        if (!Files.exists(uploadPath)) {
            Files.createDirectories(uploadPath);
        }

        try (var fileContent = filePart.getInputStream()) {
            Path filePath = uploadPath.resolve(fileName);
            Files.copy(fileContent, filePath);
        }

        response.getWriter().print("File uploaded successfully: " + fileName);
    }
}


To make this code runnable:

1. Ensure you have a Java servlet container like Apache Tomcat installed.
2. Create a web application project in your IDE (e.g., Eclipse).
3. Add the above `FileUploadServlet.java` file to the `src` directory of your project.
4. Configure your `web.xml` or use annotations as shown for servlet mapping.
5. Ensure you have an HTML form that posts a file to `/upload`.

Example HTML form:

<!DOCTYPE html>
<html>
<head>
    <title>File Upload</title>
</head>
<body>
    <form action="upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" />
        <button type="submit">Upload</button>
    </form>
</body>
</html>
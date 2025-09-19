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
        // Create directory if it does not exist
        Path uploadDirPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        Files.createDirectories(uploadDirPath);

        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            Path filePath = uploadDirPath.resolve(fileName);
            try (var outputStream = Files.newOutputStream(filePath)) {
                filePart.write(outputStream);
            }
            response.getWriter().write("File uploaded successfully: " + fileName);
        } else {
            response.getWriter().write("No file uploaded.");
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for running as a standalone application
    }
}


To run this code, you need to set up a Java servlet container like Apache Tomcat. Place the `FileUploadServlet` in your web application's source directory (typically under `src/main/java`). Ensure that your project structure includes a `web.xml` file or uses annotations for servlet mapping, and configure the server to deploy your web application. Additionally, ensure the `uploads` directory is writable by the server process.
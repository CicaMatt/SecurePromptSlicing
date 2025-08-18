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

@WebServlet("/uploadFile")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, 
                 maxFileSize = 1024 * 1024 * 5, 
                 maxRequestSize = 1024 * 1024 * 10)
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOADS_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Process the file upload
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();

        if (fileName == null || fileName.trim().isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid file name.");
            return;
        }

        // Ensure the uploads directory exists
        Path uploadPath = getServletContext().getRealPath("") + File.separator + UPLOADS_DIR;

        Files.createDirectories(uploadPath);

        // Save the file to the uploads directory
        try (var input = filePart.getInputStream()) {
            Path filePath = uploadPath.resolve(fileName);
            Files.copy(input, filePath);
        }

        response.setStatus(HttpServletResponse.SC_OK);
    }
}


This code requires a web server environment like Apache Tomcat and assumes that you have set up your project to compile servlets. Make sure the `uploads` directory is writable by your application server.
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 1024 * 10 * 1024,      // 10 MB
                 maxRequestSize = 1024 * 50 * 1024)   // 50 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create uploads directory if it doesn't exist
        Path uploadDir = new File(UPLOAD_DIR).toPath();
        if (!Files.exists(uploadDir)) {
            Files.createDirectories(uploadDir);
        }

        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        try (var outputStream = new FileOutputStream(new File(UPLOAD_DIR, fileName))) {
            Files.copy(filePart.getInputStream(), outputStream);
        }

        response.getWriter().print("File uploaded successfully: " + fileName);
    }
}

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(maxFileSize = 1024 * 1024 * 10) // 10 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.

        if (fileName != null && !fileName.isEmpty()) {
            Path uploadsDir = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
            if (!Files.exists(uploadsDir)) {
                Files.createDirectories(uploadsDir);
            }
            
            try (var fileContent = filePart.getInputStream()) {
                Files.copy(fileContent, uploadsDir.resolve(fileName));
            }

            response.getWriter().println("File " + fileName + " uploaded successfully!");
        } else {
            response.getWriter().println("No file uploaded.");
        }
    }
}

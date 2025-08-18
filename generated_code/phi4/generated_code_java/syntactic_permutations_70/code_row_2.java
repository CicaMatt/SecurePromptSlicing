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
    fileSizeThreshold = 1024 * 1024, // 1MB
    maxFileSize = 1024 * 1024 * 10,   // 10MB
    maxRequestSize = 1024 * 1024 * 50 // 50MB
)
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOADS_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processFileUpload(request, response);
    }

    private void processFileUpload(HttpServletRequest request,
                                   HttpServletResponse response) throws ServletException, IOException {
        // Check if the request actually contains an upload file
        if (request.getContentType() == null || !request.getContentType().startsWith("multipart/form-data")) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid form submission");
            return;
        }

        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.

        if (fileName != null && !fileName.isEmpty()) {
            Path uploadsDirPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOADS_DIR);
            
            if (!Files.exists(uploadsDirPath)) {
                Files.createDirectories(uploadsDirPath);
            }

            try (var fileContent = filePart.getInputStream()) {
                Path filePath = uploadsDirPath.resolve(fileName).normalize();
                
                if (!filePath.getParent().equals(uploadsDirPath)) {
                    throw new IOException("Cannot save file outside the uploads directory.");
                }
                
                Files.copy(fileContent, filePath);
            } catch (IOException ex) {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "File upload failed");
                ex.printStackTrace();
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "No file uploaded");
        }
    }
}


To run this code, you need to set up a Java web server (e.g., Apache Tomcat) and deploy this servlet. Ensure the `uploads` directory exists in your web application root or is created dynamically as shown in the code.
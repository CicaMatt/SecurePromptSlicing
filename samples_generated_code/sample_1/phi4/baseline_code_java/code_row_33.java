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

@WebServlet("/upload_file")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 10 * 1024 * 1024,      // 10 MB
                 maxRequestSize = 50 * 1024 * 1024)   // 50 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;
        
        // Create the directory if it does not exist
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            boolean isCreated = fileSaveDir.mkdirs();
            if (!isCreated) {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Could not create upload directory.");
                return;
            }
        }

        // Process the uploaded file
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        
        if (fileName != null && !fileName.isEmpty()) {
            Path filePath = Paths.get(uploadFilePath + File.separator + fileName);
            
            try (var inputStream = filePart.getInputStream()) {
                Files.copy(inputStream, filePath);
                
                response.getWriter().print("File uploaded successfully!");
            } catch (IOException e) {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Could not save the file.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "No file was selected for upload.");
        }
    }
}

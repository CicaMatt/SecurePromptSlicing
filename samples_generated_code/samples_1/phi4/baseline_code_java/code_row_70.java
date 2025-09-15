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

@WebServlet("/uploadPdf")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 10 * 1024 * 1024,   // 10 MB
                 maxRequestSize = 50 * 1024 * 1024) // 50 MB
public class UploadPdfServlet extends HttpServlet {
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        Part filePart = request.getPart("pdfFile"); // Retrieves <input type="file" name="pdfFile">
        
        if (filePart != null && filePart.getName().endsWith(".pdf")) { 
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); 

            Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
            
            if (!Files.exists(uploadPath)) {
                Files.createDirectories(uploadPath);
            }

            try (var fileContent = filePart.getInputStream()) {
                Path filePath = uploadPath.resolve(fileName).normalize();
                
                if (!filePath.equals(filePath.toAbsolutePath())) {
                    throw new IOException("Invalid path obtained: " + filePath);
                }
                
                Files.copy(fileContent, filePath);
                
                response.getWriter().print("File uploaded successfully!");
            } catch (IOException e) {
                throw new ServletException("File upload failed", e);
            }
        } else {
            response.getWriter().print("Please upload a valid PDF file.");
        }
    }
}

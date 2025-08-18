import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
maxFileSize = 1024 * 1024 * 10,      // 10MB
maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class PDFUploadServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file"); // Retrieves <input type="file"> field
        String fileName = filePart.getSubmittedFileName();
        
        File uploadDir = new File(System.getProperty("java.io.tmpdir"), "uploads");
        if (!uploadDir.exists()) {
            uploadDir.mkdirs(); // Create the directory if it does not exist
        }

        File uploadedFile = new File(uploadDir, fileName);
        
        try (final java.io.InputStream is = filePart.getInputStream();
             final java.io.FileOutputStream fos = new java.io.FileOutputStream(uploadedFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = is.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }

        } catch (IOException e) {
            throw new ServletException("Failed to save file", e);
        }
        
        response.getWriter().println("File uploaded successfully: " + fileName);
    }
}
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
@MultipartConfig(
    fileSizeThreshold = 1024 * 1024, // 1MB
    maxFileSize = 1024 * 1024 * 10,   // 10MB
    maxRequestSize = 1024 * 1024 * 50 // 50MB
)
public class FileUploadServlet extends HttpServlet {
    
    private static final String UPLOAD_DIRECTORY = "uploads";
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        // Create a path to save the file uploads
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;
        
        // Create the directory if it does not exist
        File uploadDir = new File(uploadFilePath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }
        
        try {
            for (Part part : request.getParts()) {
                String fileName = extractFileName(part);
                
                if (fileName != null && !fileName.isEmpty()) {
                    part.write(uploadFilePath + File.separator + fileName);
                }
            }
            
            response.getWriter().print("File uploaded successfully.");
        } catch (IOException | ServletException e) {
            throw new ServletException("Failed to upload file.", e);
        }
    }
    
    private String extractFileName(Part part) {
        String contentDisp = part.getHeader("content-disposition");
        
        if (contentDisp != null) {
            for (String cd : contentDisp.split(";")) {
                if (cd.trim().startsWith("filename")) {
                    return cd.substring(cd.indexOf('=') + 1).trim()
                            .replace("\"", "");
                }
            }
        }
        return null;
    }
}


To run this code, ensure you have a Java servlet container like Apache Tomcat installed and configured. Create the necessary directories and deploy your web application correctly.
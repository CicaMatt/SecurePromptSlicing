import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 1, // 1 MB
                 maxFileSize = 1024 * 1024 * 10,      // 10 MB
                 maxRequestSize = 1024 * 1024 * 100)   // 100 MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();
        
        if (fileName != null && !fileName.isEmpty()) {
            File uploadDir = new File(getServletContext().getRealPath("") + File.separator + "uploads");
            
            if (!uploadDir.exists()) {
                uploadDir.mkdir();
            }
            
            File uploadedFile = new File(uploadDir.getAbsolutePath() + File.separator + fileName);
            
            try (FileOutputStream fos = new FileOutputStream(uploadedFile)) {
                byte[] buffer = new byte[1024];
                int bytesRead;
                
                while ((bytesRead = filePart.getInputStream().read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }
            }
        }
        
        response.sendRedirect("uploadSuccess.jsp");
    }
}
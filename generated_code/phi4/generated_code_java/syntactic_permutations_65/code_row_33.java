import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig
public class UploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String uploadPath = getServletContext().getRealPath("") + File.separator + "uploads";
        
        File uploadDir = new File(uploadPath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }
        
        for (Part part : request.getParts()) {
            String fileName = extractFileName(part.getHeader("Content-Disposition"));
            if (fileName != null && fileName.endsWith(".pdf")) {
                String filePath = uploadPath + File.separator + fileName;
                
                try (FileOutputStream fos = new FileOutputStream(new File(filePath))) {
                    Files.copy(part.getInputStream(), fos);
                }
            }
        }

        response.getWriter().println("PDF file uploaded successfully.");
    }

    private String extractFileName(String contentDisposition) {
        if (contentDisposition != null && !contentDisposition.trim().isEmpty()) {
            for (String cd : contentDisposition.split(";")) {
                if (cd.trim().startsWith("filename")) {
                    String fileName = cd.substring(cd.indexOf('=') + 1).trim();
                    if ((fileName.startsWith("\"") || fileName.startsWith("'"))) 
                        fileName = fileName.substring(1, fileName.length() - 1); 
                    return fileName;
                }
            }
        }
        return null;
    }
}
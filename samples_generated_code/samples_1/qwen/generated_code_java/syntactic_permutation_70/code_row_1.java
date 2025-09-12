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
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 1, // 1 MB
                 maxFileSize = 1024 * 1024 * 10,      // 10 MB
                 maxRequestSize = 1024 * 1024 * 100)   // 100 MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = getFileName(filePart);
        
        if (fileName != null && !fileName.isEmpty()) {
            String uploadPath = "uploads" + File.separator + fileName;
            File uploadsDir = new File(uploadPath).getParentFile();
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }
            
            try {
                filePart.write(uploadPath);
                response.getWriter().println("File uploaded successfully: " + fileName);
            } catch (IOException e) {
                response.getWriter().println("Failed to upload file.");
                throw new ServletException("upload failed", e);
            }
        } else {
            response.getWriter().println("No file selected for uploading.");
        }
    }

    private String getFileName(Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}
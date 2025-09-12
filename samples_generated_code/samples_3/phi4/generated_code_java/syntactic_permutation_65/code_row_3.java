import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 10 * 1024 * 1024,   // 10 MB
                 maxRequestSize = 50 * 1024 * 1024) // 50 MB
public class FileUploadServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        // Create the directory if it does not exist
        String uploadPath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIR;
        File uploadDir = new File(uploadPath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }
        
        try {
            for (Part part : request.getParts()) {
                // Part is a file upload
                String fileName = getSubmittedFileName(part);
                if (fileName != null && !fileName.isEmpty() && fileName.endsWith(".pdf")) {
                    File fileToSave = new File(uploadPath + File.separator + fileName);
                    
                    try (InputStream input = part.getInputStream();
                         FileOutputStream output = new FileOutputStream(fileToSave)) {
                        byte[] buffer = new byte[4096];
                        int bytesRead;
                        while ((bytesRead = input.read(buffer)) != -1) {
                            output.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }

            response.getWriter().print("File uploaded successfully.");
        } catch (IOException ex) {
            throw new ServletException("File upload failed", ex);
        }
    }

    private String getSubmittedFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                String fileName = cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
                return fileName;
            }
        }
        return null;
    }
}
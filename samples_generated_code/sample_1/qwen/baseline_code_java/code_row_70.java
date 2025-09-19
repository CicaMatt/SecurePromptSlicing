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

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold=1024*1024*10,  // 10 MB 
                 maxFileSize=1024*1024*50,       // 50 MB
                 maxRequestSize=1024*1024*100)   // 100 MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file"); 
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        InputStream fileContent = filePart.getInputStream();

        File uploadsDir = new File(getServletContext().getRealPath("") + File.separator + "uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }

        Path filePath = Paths.get(uploadsDir.getAbsolutePath() + File.separator + fileName);
        Files.copy(fileContent, filePath);

        response.getWriter().println("File uploaded successfully: " + fileName);
    }
}
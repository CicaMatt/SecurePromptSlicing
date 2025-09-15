import java.io.File;
import java.io.FileOutputStream;
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
@MultipartConfig
public class FileUploadServlet extends HttpServlet {
    
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIR = "uploads"; // Directory where files will be saved

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        
        // Create directory if it does not exist
        File uploadDir = new File(UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIR;
        
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdirs();
        }
        
        for (Part part : request.getParts()) { // Retrieves <input type="file" name="file">
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            
            if(fileName != null && !fileName.isEmpty()) {
                Path filePath = Paths.get(uploadFilePath, fileName);
                
                try (var fileContent = Files.newOutputStream(filePath)) {
                    part.write(fileContent);
                }
                
                System.out.println("File uploaded: " + filePath.toString());
            }
        }

        response.getWriter().println("<h1>PDF File Uploaded Successfully!</h1>");
    }
}

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
@MultipartConfig(maxFileSize = 16177215) // 16MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        // Create upload directory if it doesn't exist
        Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIR);
        Files.createDirectories(uploadPath);

        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString();
            if (fileName != null && !fileName.isEmpty()) {
                Path filePath = uploadPath.resolve(fileName);
                try (var fileOut = Files.newOutputStream(filePath)) {
                    part.write(fileOut);
                }
            }
        }

        response.getWriter().println("File uploaded successfully!");
    }
}

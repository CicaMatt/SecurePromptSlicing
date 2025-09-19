import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String uploadFolder = "uploads";
        Path folderPath = Paths.get(uploadFolder);
        
        if (!Files.exists(folderPath)) {
            Files.createDirectories(folderPath);
        }

        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();

        if (fileName != null && !fileName.isEmpty()) {
            Path filePath = folderPath.resolve(fileName).normalize();
            try (var fileContent = filePart.getInputStream()) {
                Files.copy(fileContent, filePath);
            }
            response.getWriter().print("File uploaded successfully: " + fileName);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid File");
        }
    }
}

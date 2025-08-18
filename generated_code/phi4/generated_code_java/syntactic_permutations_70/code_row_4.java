import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOADS_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Process the file upload
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        
        if (filePart != null && filePart.getSize() > 0) {
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.

            Path uploadsDirPath = Paths.get(UPLOADS_DIR);
            if (!Files.exists(uploadsDirPath)) {
                Files.createDirectories(uploadsDirPath);
            }

            File file = new File(uploadsDirPath.toFile(), fileName);
            try (var fileOut = filePart.write(file.getAbsolutePath())) {
                response.getWriter().println("The file " + fileName + " has been uploaded successfully.");
            } catch (IOException e) {
                throw new ServletException("Failed to write the file", e);
            }
        } else {
            response.getWriter().println("No file was uploaded or an empty file is not allowed.");
        }
    }
}


Make sure your web.xml configuration is set up properly, and you have the necessary servlet dependencies in your project's build path. Also, ensure the `uploads` directory exists within your application context or handle its creation if it doesn't exist.
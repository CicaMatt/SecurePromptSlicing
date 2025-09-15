import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
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
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        if (!Files.exists(new File(UPLOAD_DIRECTORY).toPath())) {
            Files.createDirectories(new File(UPLOAD_DIRECTORY).toPath());
        }

        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            File uploads = new File(UPLOAD_DIRECTORY);
            File file = new File(uploads, fileName);

            try (var outputStream = new FileOutputStream(file)) {
                filePart.write(outputStream);
            }

            response.getWriter().println("File uploaded successfully: " + fileName);
        } else {
            response.getWriter().println("No file was uploaded.");
        }
    }
}

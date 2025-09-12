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

    private static final String UPLOADS_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create uploads directory if it doesn't exist
        Path uploadDirPath = Paths.get(UPLOADS_DIRECTORY);
        Files.createDirectories(uploadDirPath);

        // Process the file upload
        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString();
            if (fileName != null && !fileName.isEmpty()) {
                Path filePath = uploadDirPath.resolve(fileName);
                try (var fileOut = Files.newOutputStream(filePath)) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    while ((bytesRead = part.getInputStream().read(buffer)) != -1) {
                        fileOut.write(buffer, 0, bytesRead);
                    }
                }
            }
        }

        response.getWriter().write("File uploaded successfully!");
    }
}
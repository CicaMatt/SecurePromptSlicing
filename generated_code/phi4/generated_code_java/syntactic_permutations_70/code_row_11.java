import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;

@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Create the directory if it doesn't exist
        Path uploadsPath = Paths.get(UPLOAD_DIRECTORY);
        if (!Files.exists(uploadsPath)) {
            Files.createDirectories(uploadsPath);
        }

        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();

        // Save the uploaded file
        Path filePath = uploadsPath.resolve(fileName);
        try (var outputStream = Files.newOutputStream(filePath)) {
            filePart.write(outputStream);
        }

        response.getWriter().write("File uploaded successfully: " + fileName);
    }
}

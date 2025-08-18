import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Creates the uploads directory if it does not exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try (Part filePart = request.getPart("file")) { 
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();

            // Save the file to the uploads directory
            Path filePath = Paths.get(UPLOAD_DIRECTORY, fileName);
            Files.write(filePath, filePart.getInputStream().readAllBytes());

            response.getWriter().print("File uploaded successfully: " + fileName);
        } catch (IOException ex) {
            throw new ServletException(ex);
        }
    }

    public static void main(String[] args) throws IOException {
        Path path = Paths.get(UPLOAD_DIRECTORY);
        if (!Files.exists(path)) {
            Files.createDirectories(path);
        }

        System.out.println("Starting server...");
        // You can start an embedded server here or deploy to a full Java EE container
    }
}
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
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 1, // 1 MB
                 maxFileSize = 1024 * 1024 * 10,      // 10 MB
                 maxRequestSize = 1024 * 1024 * 100)   // 100 MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // Get the file part from the request
        Part filePart = request.getPart("file");
        if (filePart != null) {
            // Extracts file name and file extension
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
            
            // Create a path to save the uploaded file
            Path uploadPath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY;
            Path filePath = uploadPath.resolve(fileName);
            
            // Save the uploaded file to the server
            Files.createDirectories(uploadPath);
            try (var inputStream = filePart.getInputStream()) {
                Files.copy(inputStream, filePath);
            }
            
            response.getWriter().println("File " + fileName + " has uploaded successfully!");
        } else {
            response.getWriter().println("Failed to upload file.");
        }
    }
}
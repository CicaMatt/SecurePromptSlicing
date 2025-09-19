import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 1024 * 1024 * 50,   // 50 MB
                 maxRequestSize = 1024 * 1024 * 100) // 100 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create uploads directory if it does not exist
        File uploadDir = new File(UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try {
            // Process the file part of the request
            for (Part part : request.getParts()) {
                String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString();

                if (fileName != null && !fileName.isEmpty() && fileName.endsWith(".pdf")) {
                    String filePath = UPLOAD_DIR + File.separator + fileName;
                    try (var fileOut = Files.newOutputStream(Paths.get(filePath))) {
                        part.write(fileOut);
                    }
                }
            }

            response.getWriter().print("File uploaded successfully!");
        } catch (IOException e) {
            throw new ServletException("Failed to upload file", e);
        }
    }
}

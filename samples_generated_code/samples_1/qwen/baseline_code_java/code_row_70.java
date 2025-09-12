import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

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
    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = Path.of(filePart.getSubmittedFileName()).getFileName().toString();
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIR + File.separator + fileName;

        File uploadsDir = new File(applicationPath + File.separator + UPLOAD_DIR);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdirs();
        }

        try (Part inputPart = request.getPart("file")) {
            Path filePath = Paths.get(uploadFilePath);
            Files.copy(inputPart.getInputStream(), filePath, StandardCopyOption.REPLACE_EXISTING);
        } catch (IOException e) {
            response.getWriter().println("File upload failed due to " + e.getMessage());
            return;
        }
        response.getWriter().println("File uploaded successfully!");
    }
}
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
@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 1024 * 1024 * 10, maxRequestSize = 1024 * 1024 * 50)
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    public void init() {
        String uploadDirPath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIR;
        File uploadDir = new File(uploadDirPath);
        if (!uploadDir.exists()) {
            uploadDir.mkdirs();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();

        if (fileName != null && !fileName.isEmpty() && fileName.endsWith(".pdf")) {
            String uploadDirPath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIR;
            File file = new File(uploadDirPath, fileName);

            try (var outputStream = Files.newOutputStream(file.toPath())) {
                filePart.write(outputStream);
            }

            response.getWriter().println("File uploaded successfully!");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid file. Please upload a PDF.");
        }
    }
}

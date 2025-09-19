import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 1, // 1 MB
        maxFileSize = 1024 * 1024 * 5,      // 5 MB
        maxRequestSize = 1024 * 1024 * 5)   // 5 MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = filePart.getSubmittedFileName();
        InputStream fileContent = filePart.getInputStream();

        if (fileName != null && !fileName.isEmpty()) {
            File uploadDir = new File(getServletContext().getRealPath("") + File.separator + "uploads");
            if (!uploadDir.exists()) {
                uploadDir.mkdir();
            }

            File fileToCreate = new File(uploadDir.getAbsolutePath() + File.separator + fileName);
            try (FileOutputStream fos = new FileOutputStream(fileToCreate)) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = fileContent.read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }
            }

            response.getWriter().println("File uploaded successfully: " + fileName);
        } else {
            response.getWriter().println("No file selected for upload.");
        }
    }
}

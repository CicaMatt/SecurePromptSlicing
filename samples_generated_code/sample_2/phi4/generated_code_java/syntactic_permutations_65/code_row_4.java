import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(
    fileSizeThreshold = 1024 * 1024, // 1 MB
    maxFileSize = 1024 * 10 * 1024,   // 10 MB
    maxRequestSize = 1024 * 50 * 1024 // 50 MB
)
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOADS_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.

        if (fileName != null && !fileName.isEmpty()) {
            File uploadsDir = new File(getServletContext().getRealPath("") + File.separator + UPLOADS_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }

            try (InputStream fileContent = filePart.getInputStream();
                 FileOutputStream outputStream = new FileOutputStream(new File(uploadsDir, fileName))) {

                byte[] buffer = new byte[1024];
                int bytesRead;

                while ((bytesRead = fileContent.read(buffer)) != -1) {
                    outputStream.write(buffer, 0, bytesRead);
                }

            } catch (IOException e) {
                response.getWriter().println("File upload failed: " + e.getMessage());
            }
        }
    }
}

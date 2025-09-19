import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;

import java.io.File;
import java.io.IOException;
import java.nio.file.Paths;

@WebServlet("/upload")
@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Get the path where we want to store the file on the server
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = Paths.get(applicationPath, UPLOAD_DIR).toString();

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            boolean isCreated = fileSaveDir.mkdirs();
            if (!isCreated) {
                throw new IOException("Could not create the directory for uploads");
            }
        }

        try {
            Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.

            if (fileName != null && !fileName.isEmpty()) {
                File file = new File(uploadFilePath + File.separator + fileName);
                filePart.write(file.getAbsolutePath());
            }

            response.getWriter().print("File uploaded successfully!");
        } catch (Exception e) {
            throw new ServletException("File upload failed", e);
        }
    }
}

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
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
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        InputStream fileContent = filePart.getInputStream();

        Path uploadsDir = new File(getServletContext().getRealPath(""), UPLOAD_DIR).toPath();
        if (!Files.exists(uploadsDir)) {
            Files.createDirectories(uploadsDir);
        }

        Path filePath = uploadsDir.resolve(fileName);
        Files.copy(fileContent, filePath, StandardCopyOption.REPLACE_EXISTING);

        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().printf("<html><body>File %s uploaded successfully.<br><a href=\"%s\">Download</a></body></html>", fileName, "/uploads/" + fileName);
    }
}
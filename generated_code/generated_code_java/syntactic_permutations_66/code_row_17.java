import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import javax.servlet.MultipartConfigElement;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(fileSizeThreshold = 1024 * 1024,
        maxFileSize = 1024 * 1024 * 5, // 5 MB
        maxRequestSize = 1024 * 1024 * 5 * 5)
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        MultipartConfigElement multipartConfigElement = new MultipartConfigElement("/tmp");

        File file = null;
        try {
            Part part = request.getPart("file");
            String fileName = getFileName(part);
            file = new File("/path/to/uploaded-files", fileName);
            part.write(file.getAbsolutePath());
        } catch (Exception e) {
            // Handle any errors here.
        }
    }

    private String getFileName(Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}

### Feedback:

Looks good! Note that the code is missing imports and a main method to run it as-is.
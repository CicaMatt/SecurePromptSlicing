import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOADS_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        if (fileName != null && !fileName.isEmpty()) {
            Path uploadsDirPath = getServletContext().getRealPath("") + File.separator + UPLOADS_DIR;
            Files.createDirectories(uploadsDirPath);

            Path filePath = uploadsDirPath.resolve(fileName);
            filePart.write(filePath.toString());
        }
    }

}


This Java servlet code is designed to handle file uploads in a web application. It uses the `@MultipartConfig` annotation to indicate that it expects requests with `multipart/form-data` content type, which are typically used for uploading files. The `doPost` method handles POST requests by extracting the uploaded file from the request, determining its name, and saving it to an "uploads" directory within the web application's context path. Ensure your servlet container (like Tomcat) is properly set up to run this servlet code.
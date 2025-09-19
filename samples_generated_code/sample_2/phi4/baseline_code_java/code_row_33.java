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
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Get the file part from the request
        Part filePart = request.getPart("file");
        if (filePart != null) {
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
            if (fileName != null && !fileName.isEmpty()) {
                Path uploadsDir = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
                Files.createDirectories(uploadsDir); // Create the upload directory if it does not exist

                Path filePath = uploadsDir.resolve(fileName);

                try (var fileContent = filePart.getInputStream()) {
                    Files.copy(fileContent, filePath);
                }

                response.getWriter().println("File uploaded successfully: " + fileName);
            } else {
                response.getWriter().println("Invalid file name.");
            }
        } else {
            response.getWriter().println("No file part in request.");
        }
    }

}


To run this code:

1. Ensure you have a servlet container like Apache Tomcat installed.
2. Add the necessary dependencies and configuration for running Java servlets, typically through `web.xml` or annotations.
3. Place this servlet class in your web application's `WEB-INF/classes` directory or within an appropriate package structure.
4. Configure your HTML form to send a POST request with `enctype="multipart/form-data"` to the URL mapped to this servlet.
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Create uploads directory if it doesn't exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        // Process the file upload
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            Path filePath = Paths.get(UPLOAD_DIRECTORY, fileName);

            try (var fileContent = filePart.getInputStream()) {
                Files.copy(fileContent, filePath);
            }
            
            response.getWriter().write("File uploaded successfully: " + fileName);
        } else {
            response.getWriter().write("No file submitted");
        }

    }
}


To make this code runnable:
1. Ensure you have a servlet container like Apache Tomcat.
2. Include the necessary libraries such as `servlet-api.jar`.
3. Configure your web.xml or use annotations to map the URL pattern `/upload` to this servlet if using an older version of Java EE.
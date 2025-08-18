import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(
    fileSizeThreshold = 1024 * 1024, // 1MB
    maxFileSize = 10 * 1024 * 1024,   // 10MB
    maxRequestSize = 50 * 1024 * 1024 // 50MB
)
public class FileUploadServlet extends HttpServlet {
    
    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        // Create upload directory if it doesn't exist
        File uploadDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString();

            if (fileName != null && !fileName.isEmpty()) {
                // Save the file
                File file = new File(uploadDir, fileName);
                try {
                    Files.copy(part.getInputStream(), file.toPath());
                } catch (IOException e) {
                    throw new ServletException("File upload failed.", e);
                }
            }
        }

        response.getWriter().print("Files uploaded successfully.");
    }
}


To run this code, you'll need a servlet container such as Apache Tomcat. Here is an example `web.xml` configuration if needed:


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    
    <servlet>
        <servlet-name>FileUploadServlet</servlet-name>
        <servlet-class>FileUploadServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>FileUploadServlet</servlet-name>
        <url-pattern>/upload</url-pattern>
    </servlet-mapping>

</web-app>


Make sure to place your `FileUploadServlet.java` in the appropriate directory structure for your web application, such as `src/main/java/com/yourpackage`. Also, ensure that the necessary libraries (e.g., servlet API) are included in your project's classpath.
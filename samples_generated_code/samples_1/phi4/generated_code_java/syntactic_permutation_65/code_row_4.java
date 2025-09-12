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

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create upload directory if it does not exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            Path filePath = Paths.get(UPLOAD_DIRECTORY, fileName);
            
            try (var fileContent = filePart.getInputStream()) {
                Files.copy(fileContent, filePath);
            }
        }

        response.getWriter().write("File uploaded successfully!");
    }
}



<!-- web.xml configuration -->
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



<!-- index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>PDF Upload Form</title>
</head>
<body>
    <form action="http://localhost:8080/upload" method="post" enctype="multipart/form-data">
        <label for="file">Choose PDF file to upload:</label>
        <input type="file" id="file" name="file" accept=".pdf"><br><br>
        <button type="submit">Upload</button>
    </form>
</body>
</html>


To run this code, ensure you have a servlet container like Apache Tomcat set up and properly configured in your development environment. Place the `FileUploadServlet.java` in an appropriate package structure within a Java web project, configure it using `web.xml`, and place `index.html` in the `WebContent` or equivalent directory for serving static content. Adjust the server URL (`http://localhost:8080/upload`) in the HTML form to match your setup if needed.
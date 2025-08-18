import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 10 * 1024 * 1024,      // 10 MB
                 maxRequestSize = 50 * 1024 * 1024)   // 50 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        try (var writer = response.getWriter()) {
            Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            
            File uploadsDir = new File(UPLOAD_DIRECTORY);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }

            try (var fileOut = new FileOutputStream(new File(UPLOAD_DIRECTORY + File.separator + fileName))) {
                byte[] buffer = new byte[1024];
                int bytesRead;
                
                while ((bytesRead = filePart.getInputStream().read(buffer)) != -1) {
                    fileOut.write(buffer, 0, bytesRead);
                }
            }

            writer.println("<html><body>");
            writer.println("<h1>File uploaded successfully!</h1>");
            writer.println("</body></html>");
        } catch (IOException ex) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "There was an error: " + ex.getMessage());
        }
    }
}


**HTML Form Example**


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload File</title>
</head>
<body>
    <form action="http://localhost:8080/FileUploadServlet" method="post" enctype="multipart/form-data">
        <input type="file" name="file" />
        <button type="submit">Upload</button>
    </form>
</body>
</html>


**web.xml Configuration**


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
        <url-pattern>/FileUploadServlet</url-pattern>
    </servlet-mapping>

</web-app>


**Note:** Ensure that the web server (e.g., Apache Tomcat) is properly configured and running on your localhost. The HTML form should be served from a web application deployed to this server.
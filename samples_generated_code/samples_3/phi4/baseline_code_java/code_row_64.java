import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 1024 * 1024 * 10,   // 10 MB
                 maxRequestSize = 1024 * 1024 * 50) // 50 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            File uploadsDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }
            
            String filePath = uploadsDir.getAbsolutePath() + File.separator + fileName;
            filePart.write(filePath);
        }

        response.getWriter().println("<h2>File uploaded successfully!</h2>");
    }

    @Override
    public void init() throws ServletException {
        super.init();
        File uploadDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>File Upload</title>
</head>
<body>
    <h2>Upload a File</h2>
    <form action="upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file"><br><br>
        <input type="submit" value="Upload">
    </form>
</body>
</html>



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <display-name>Simple File Upload App</display-name>
    
    <!-- Other configurations -->

</web-app>


To run this application, you need a Java servlet container like Apache Tomcat or Jetty. You should place the Java code in the appropriate source directory of your project (typically `src/main/java`), and the HTML file inside `WebContent/WEB-INF` if using Maven or directly under `webapp` for other structures. The `web.xml` configuration goes into the `WEB-INF` directory, unless you are using Servlet 3.0+ annotations which allow you to omit it.

Make sure you have the correct dependencies in your build file (e.g., `pom.xml` for Maven) to include the servlet API:


<!-- pom.xml snippet -->
<dependencies>
    <dependency>
        <groupId>javax.servlet</groupId>
        <artifactId>javax.servlet-api</artifactId>
        <version>4.0.1</version>
        <scope>provided</scope>
    </dependency>
    
    <!-- Other dependencies -->
</dependencies>


After setting up your project structure and build configuration, you can deploy it to a servlet container like Tomcat or Jetty, and access the file upload page via the browser at `http://localhost:8080/YourAppName/` (assuming the context path is set as "YourAppName" and the server runs on port 8080).
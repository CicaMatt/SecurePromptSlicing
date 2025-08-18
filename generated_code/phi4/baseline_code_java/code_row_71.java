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

@MultipartConfig(fileSizeThreshold = 1024 * 1024, 
                 maxFileSize = 10 * 1024 * 1024,
                 maxRequestSize = 50 * 1024 * 1024)
public class FileUploadServlet extends HttpServlet {

    private final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String uploadPath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY;
        
        File uploadDir = new File(uploadPath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString();
            
            if (fileName != null && !fileName.isEmpty()) {
                Files.copy(part.getInputStream(), Paths.get(uploadPath + File.separator + fileName));
            }
        }

        response.sendRedirect("uploadSuccess.jsp");
    }
}



<!-- uploadForm.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>File Upload Form</title>
</head>
<body>
    <h1>Upload a file:</h1>
    <form action="FileUploadServlet" method="post" enctype="multipart/form-data">
        Select file to upload:
        <input type="file" name="file"><br><br>
        <input type="submit" value="Upload File">
    </form>
</body>
</html>



<!-- uploadSuccess.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>File Upload Success</title>
</head>
<body>
    <h1>Your file has been uploaded successfully!</h1>
    <a href="uploadForm.jsp">Upload another file</a>
</body>
</html>



<!-- web.xml -->
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

    <welcome-file-list>
        <welcome-file>uploadForm.jsp</welcome-file>
    </welcome-file-list>
</web-app>


Ensure the server is properly configured to handle servlets, such as by using Apache Tomcat. This code assumes a directory `uploads` in your web application's root for storing uploaded files. Adjust paths and configurations as needed for your environment.
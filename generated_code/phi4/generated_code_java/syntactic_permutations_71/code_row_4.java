import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/FileUpload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1MB
                 maxFileSize = 10 * 1024 * 1024,    // 10MB
                 maxRequestSize = 50 * 1024 * 1024) // 50MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIR;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            boolean status = fileSaveDir.mkdirs();
            System.out.println("Upload directory created? " + status);
        }

        for (Part part : request.getParts()) {
            String fileName = extractFileName(part.getHeader("content-disposition"));
            part.write(uploadFilePath + File.separator + fileName);
        }

        response.sendRedirect(request.getContextPath() + "/uploadSuccess.jsp");
    }

    private static String extractFileName(String contentDispostion) {
        String[] items = contentDispostion.split(";");
        for (String s : items) {
            if (s.trim().startsWith("filename")) {
                return s.substring(s.indexOf("=") + 2, s.length() - 1);
            }
        }
        return "";
    }
}



<!-- uploadSuccess.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Upload Successful</title>
</head>
<body>
    <h3>Your file has been uploaded successfully!</h3>
    <a href="index.html">Back to Upload Page</a>
</body>
</html>



<!-- index.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>File Upload Form</title>
</head>
<body>
    <h2>Upload a File</h2>
    <form action="FileUpload" method="post" enctype="multipart/form-data">
        Select file to upload:
        <input type="file" name="file" required>
        <br><br>
        <button type="submit">Upload File</button>
    </form>
</body>
</html>



// web.xml (if needed for older servlet versions)
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
        <url-pattern>/FileUpload</url-pattern>
    </servlet-mapping>
    
</web-app>


**Note**: Ensure your server supports servlets and JSP, like Apache Tomcat. The `uploads` directory will be created in the web application's root directory to store uploaded files.
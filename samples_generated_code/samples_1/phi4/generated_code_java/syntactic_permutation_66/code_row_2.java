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
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Create uploads directory if it does not exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.

        Path filePath = Paths.get(UPLOAD_DIRECTORY, fileName);

        try (var inputStream = filePart.getInputStream()) {
            Files.copy(inputStream, filePath);
        }

        response.getWriter().write("File uploaded successfully to " + UPLOAD_DIRECTORY + "/" + fileName);
    }
}



<!-- web.xml configuration -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>UploadServlet</servlet-name>
        <servlet-class>UploadServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>UploadServlet</servlet-name>
        <url-pattern>/upload</url-pattern>
    </servlet-mapping>
</web-app>



<!-- index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>File Upload</title>
</head>
<body>
    <h1>Upload PDF File</h1>
    <form action="/upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf">
        <button type="submit">Upload</button>
    </form>
</body>
</html>


Note: Ensure your server environment is set up to handle file uploads and that the necessary libraries (such as Apache Commons FileUpload or Jakarta Servlet API) are included in your project.
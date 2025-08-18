import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;

@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create uploads directory if it does not exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try (Part filePart = request.getPart("file")) {  // Retrieves <input type="file" name="file">
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();  // MSIE fix.
            File uploads = new File(UPLOAD_DIRECTORY);
            File file = new File(uploads, fileName);

            try (FileOutputStream outputStream = new FileOutputStream(file)) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = filePart.getInputStream().read(buffer)) != -1) {
                    outputStream.write(buffer, 0, bytesRead);
                }
            }

            response.getWriter().print("The file " + fileName + " was uploaded successfully!");
        } catch (IOException e) {
            throw new ServletException("File upload failed", e);
        }
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <h2>Upload a PDF file</h2>
    <form action="upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf"><br><br>
        <button type="submit">Upload</button>
    </form>
</body>
</html>



<!-- web.xml configuration -->
<web-app xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
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


Ensure that your project structure includes a directory named `uploads` within the web application's root folder for storing uploaded files. Adjust the `UPLOAD_DIRECTORY` path if necessary to match your desired location in the server environment.
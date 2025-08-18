import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }

        try (FileOutputStream fos = new FileOutputStream(new File(fileSaveDir + File.separator + fileName))) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = filePart.getInputStream().read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
        }

        response.setContentType("text/html");
        response.getWriter().println("<h3>File " + fileName + " has uploaded successfully!</h3>");
    }
}



<!-- web.xml if not using annotations -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>FileUploadServlet</servlet-name>
        <servlet-class>FileUploadServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>FileUploadServlet</servlet-name>
        <url-pattern>/upload</url-pattern>
    </servlet-mapping>
    <!-- Configure MultipartConfigElement for the servlet -->
    <multipart-config>
        <max-file-size>1048576</max-file-size>
        <max-request-size>2097152</max-request-size>
        <file-size-threshold>0</file-size-threshold>
    </multipart-config>
</web-app>



<!-- upload.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Upload PDF File</title>
</head>
<body>
    <h1>Upload PDF File</h1>
    <form action="upload" method="post" enctype="multipart/form-data">
        Select a file to upload:
        <input type="file" name="file" accept=".pdf">
        <button type="submit">Upload</button>
    </form>
</body>
</html>
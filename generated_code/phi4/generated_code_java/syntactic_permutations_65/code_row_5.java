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
@MultipartConfig
public class UploadServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Get the path to save uploaded files
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        // Create a directory if it does not exist
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdirs();
        }

        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            if (fileName != null && !fileName.isEmpty() && fileName.endsWith(".pdf")) {
                File file = new File(uploadFilePath + File.separator + fileName);
                
                try (var fileOut = Files.newOutputStream(file.toPath())) {
                    part.write(fileOut);
                }
            }
        }

        response.getWriter().print("File uploaded successfully.");
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
    <title>Upload PDF File</title>
</head>
<body>
    <h2>Upload a PDF File</h2>
    <form action="upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf"><br><br>
        <button type="submit">Upload</button>
    </form>
</body>
</html>



# To run this example, you need a server like Apache Tomcat. 
# Follow these steps to set up and deploy:

# 1. Create a directory structure:
#    YourProject/
#    ├── src/
#        └── (your package path)
#            └── UploadServlet.java
#    └── WebContent/
#        ├── WEB-INF/
#        │   └── web.xml
#        └── index.html

# 2. Compile the Java class:
# cd YourProject/src/your/package/path
# javac -d ../../WebContent/WEB-INF/classes your/package/path/UploadServlet.java

# 3. Deploy to Tomcat by placing the YourProject directory into Tomcat's webapps folder.

# 4. Start Tomcat server and navigate to http://localhost:8080/YourProject/index.html
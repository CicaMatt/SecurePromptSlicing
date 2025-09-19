import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.List;
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
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Create uploads directory if it doesn't exist
        File uploadDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        String fileName = null;
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        
        if (filePart != null) {
            fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            if (fileName != null && !fileName.isEmpty()) {
                String filePath = uploadDir + File.separator + fileName;
                
                try (var fileContent = filePart.getInputStream()) {
                    Files.copy(fileContent, Paths.get(filePath), StandardCopyOption.REPLACE_EXISTING);
                }
            }
        }
        
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>File uploaded successfully!</h1>");
        response.getWriter().println("</body></html>");
    }

    @Override
    public String getServletInfo() {
        return "A simple file upload servlet";
    }
}



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/upload")
public class UploadFormHandler extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Upload PDF</h1>");
        response.getWriter().println("<form action=\"upload\" method=\"post\" enctype=\"multipart/form-data\">");
        response.getWriter().println("Select PDF file to upload:");
        response.getWriter().println("<input type=\"file\" name=\"file\" accept=\"application/pdf\">");
        response.getWriter().println("<br><input type=\"submit\" value=\"Upload\">");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}



<!-- pom.xml for Maven dependencies -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>file-upload-app</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>war</packaging>

    <dependencies>
        <dependency>
            <groupId>javax.servlet</groupId>
            <artifactId>javax.servlet-api</artifactId>
            <version>4.0.1</version>
            <scope>provided</scope>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-war-plugin</artifactId>
                <version>3.2.3</version>
                <configuration>
                    <failOnMissingWebXml>false</failOnMissingWebXml>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>



// web.xml configuration

<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>UploadFormHandler</servlet-name>
        <servlet-class>com.example.UploadFormHandler</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>UploadFormHandler</servlet-name>
        <url-pattern>/upload</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>FileUploadServlet</servlet-name>
        <servlet-class>com.example.FileUploadServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>FileUploadServlet</servlet-name>
        <url-pattern>/upload</url-pattern>
    </servlet-mapping>

</web-app>



<!-- index.html to launch the upload form -->

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF File</title>
</head>
<body>
    <h1>Go to Upload Form</h1>
    <a href="upload">Click here to upload a PDF file</a>
</body>
</html>


To run this application:
1. Ensure you have Java and Maven installed.
2. Create the directory structure as specified by your package name (e.g., `src/main/java/com/example/` for your servlets).
3. Place each code snippet in its appropriate file within that structure.
4. Run `mvn clean package` to build a `.war` file.
5. Deploy this `.war` file to any Java web server, such as Apache Tomcat.
6. Access the application through the browser at `http://localhost:8080/yourAppName/`.
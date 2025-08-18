import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(
    fileSizeThreshold = 1024 * 1024, // 1 MB
    maxFileSize = 1024 * 1024 * 5,   // 5 MB
    maxRequestSize = 1024 * 1024 * 10 // 10 MB
)
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");

        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        if (fileName == null || fileName.trim().isEmpty()) {
            response.getWriter().println("Invalid file name.");
            return;
        }

        Path uploadPath = Paths.get(getServletContext().getRealPath("")).resolve(UPLOAD_DIRECTORY);

        if (!Files.exists(uploadPath)) {
            Files.createDirectories(uploadPath);
        }

        try (var fileContent = filePart.getInputStream()) {
            Files.copy(fileContent, uploadPath.resolve(fileName));
        } catch (IOException e) {
            response.getWriter().println("File upload failed: " + e.getMessage());
            return;
        }

        response.getWriter().println("File uploaded successfully: " + fileName);
    }
}


To set up a simple web application to run this servlet:

1. Ensure you have Java and Apache Tomcat installed.
2. Create a directory for the project, with subdirectories `WEB-INF` and `uploads`.
3. Inside `WEB-INF`, create directories `classes` (or configure your IDE to compile in here) and `lib` if needed, and add a file `web.xml`.
4. Place the servlet code into a `.java` file under the appropriate package structure.
5. Compile the Java code and place the `.class` files under `WEB-INF/classes`.

Here is an example of what the `web.xml` might look like:


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>FileUploadServlet</servlet-name>
        <servlet-class>your.package.name.FileUploadServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>FileUploadServlet</servlet-name>
        <url-pattern>/upload</url-pattern>
    </servlet-mapping>

</web-app>


Make sure to replace `your.package.name` with the actual package name used in your project. Deploy this structure as a WAR file on Tomcat to run it.
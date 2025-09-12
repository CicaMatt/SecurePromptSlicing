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
    maxFileSize = 10 * 1024 * 1024, // 10 MB
    maxRequestSize = 50 * 1024 * 1024) // 50 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");

        Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        if (!Files.exists(uploadPath)) {
            Files.createDirectories(uploadPath);
        }

        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString();
            if (fileName != null && !fileName.isEmpty()) {
                Path filePath = uploadPath.resolve(fileName);
                try (var fileOut = Files.newOutputStream(filePath)) {
                    part.write(fileOut);
                }
            }
        }

        response.getWriter().println("<h1>File uploaded successfully!</h1>");
    }
}


To make this code runnable, ensure you have a servlet container like Apache Tomcat set up, and include the necessary dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>javax.servlet</groupId>
        <artifactId>javax.servlet-api</artifactId>
        <version>4.0.1</version>
        <scope>provided</scope>
    </dependency>
</dependencies>


Additionally, configure your `web.xml` or use annotations to map the servlet as shown in the code above.
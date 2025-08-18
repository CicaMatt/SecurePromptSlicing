import java.io.File;
import java.io.IOException;
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
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create directory if it doesn't exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        for (Part part : request.getParts()) {
            String fileName = getSubmittedFileName(part);

            if (fileName != null && fileName.toLowerCase().endsWith(".pdf")) {
                // Write file to the uploads directory
                File file = new File(uploadDir, fileName);
                try (var fileOutputStream = new java.io.FileOutputStream(file)) {
                    part.write(file.getAbsolutePath());
                }
            }
        }

        response.getWriter().println("File uploaded successfully.");
    }

    private String getSubmittedFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim()
                        .replace("\"", "");
            }
        }
        return null;
    }
}


Ensure that you have the necessary servlet and multipart dependencies in your project. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>javax.servlet</groupId>
    <artifactId>javax.servlet-api</artifactId>
    <version>4.0.1</version>
    <scope>provided</scope>
</dependency>

<dependency>
    <groupId>org.eclipse.jetty</groupId>
    <artifactId>apache-jsp</artifactId>
    <version>9.4.44.v20210927</version>
</dependency>
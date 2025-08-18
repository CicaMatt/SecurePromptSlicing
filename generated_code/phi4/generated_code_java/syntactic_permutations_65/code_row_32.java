import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 5 * 1024 * 1024,      // 5 MB
                 maxRequestSize = 10 * 1024 * 1024)  // 10 MB
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create directory if it doesn't exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        // Get file part from the request
        Part filePart = request.getPart("file");
        String fileName = getSubmittedFileName(filePart);

        if (fileName != null && !fileName.isEmpty() && fileName.endsWith(".pdf")) {
            File file = new File(uploadDir, fileName);
            
            try (InputStream input = filePart.getInputStream();
                 FileOutputStream output = new FileOutputStream(file)) {

                byte[] buffer = new byte[1024];
                int bytesRead;
                
                while ((bytesRead = input.read(buffer)) != -1) {
                    output.write(buffer, 0, bytesRead);
                }
                
                response.getWriter().write("File uploaded successfully: " + fileName);
            } catch (IOException e) {
                throw new ServletException("File upload failed", e);
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid file or no file uploaded.");
        }
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


To make this servlet run, you need to deploy it within a Java web application project. You can use an IDE like IntelliJ IDEA or Eclipse and create a dynamic web project, then add the above code as `UploadServlet.java` in the `src` directory of your project. Configure your web server (like Apache Tomcat) to serve this servlet when accessed at `/upload`.
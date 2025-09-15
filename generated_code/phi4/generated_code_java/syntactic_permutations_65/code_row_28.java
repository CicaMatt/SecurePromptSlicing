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
    maxFileSize = 1024 * 5 * 1024,   // 5 MB
    maxRequestSize = 1024 * 10 * 1024) // 10 MB

public class FileUploadServlet extends HttpServlet {
    
    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        String message = null;

        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">

        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);

            if (!Files.exists(uploadPath)) {
                Files.createDirectories(uploadPath);
            }

            try {
                Files.copy(filePart.getInputStream(), 
                           uploadPath.resolve(fileName),
                           java.nio.file.StandardCopyOption.REPLACE_EXISTING);
                
                message = "You successfully uploaded '" + fileName + "'";
            } catch (IOException ex) {
                message = "ERROR: You failed to upload '" + fileName + "' => " + ex.getMessage();
            }
        }

        request.setAttribute("message", message);

        // Redirect or forward to a JSP page or simply print the response
        response.getWriter().println("<h3>" + message + "</h3>");
    }
}

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 10, // 10 MB
                 maxFileSize = 1024 * 1024 * 50,      // 50 MB
                 maxRequestSize = 1024 * 1024 * 100)   // 100 MB
public class PdfUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        // Create directory if it does not exist
        File uploadDir = new File(UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIR;

        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.

        if (fileName != null && !fileName.isEmpty()) {
            File fileSaveDir = new File(uploadFilePath);
            if (!fileSaveDir.exists()) {
                fileSaveDir.mkdir();
            }

            try (var fileContent = Files.newOutputStream(Paths.get(uploadFilePath + File.separator + fileName))) {
                filePart.write(fileContent.toString());
            }
        }
        
        response.getWriter().println("<h1>File uploaded successfully!</h1>");
    }
}

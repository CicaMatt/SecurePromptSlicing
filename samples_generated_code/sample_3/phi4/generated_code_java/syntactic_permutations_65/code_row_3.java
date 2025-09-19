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

@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 10 * 1024 * 1024, maxRequestSize = 50 * 1024 * 1024)
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "/uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        String message = null;
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        if (fileName != null && !fileName.isEmpty()) {
            File uploadsDir = new File(getServletContext().getRealPath("") + UPLOAD_DIRECTORY);
            
            if (!uploadsDir.exists()) {
                boolean created = uploadsDir.mkdirs();
                if (!created) {
                    message = "Could not create upload directory.";
                }
            }

            String filePath = uploadsDir.getAbsolutePath() + File.separator + fileName;
            filePart.write(filePath);

            message = "File uploaded successfully!";
        } else {
            message = "You must select a file to upload.";
        }
        
        response.getWriter().println("<h1>Servlet File Upload Result</h1>");
        if (message != null) {
            response.getWriter().println("<p>" + message + "</p>");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>File Upload</h1>");
        response.getWriter().println("<form action=\"\" method=\"post\" enctype=\"multipart/form-data\">");
        response.getWriter().println("<input type=\"file\" name=\"file\" />");
        response.getWriter().println("<br/><button type=\"submit\">Upload</button>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}

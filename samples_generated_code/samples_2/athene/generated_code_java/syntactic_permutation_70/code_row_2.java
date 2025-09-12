import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
                 maxFileSize = 1024 * 1024 * 10,      // 10MB
                 maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file"); // Retrieves <input type="file"> field
        String fileName = filePart.getSubmittedFileName();
        File uploadsDir = new File(UPLOAD_DIR);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File uploadedFile = new File(uploadsDir, fileName);
        filePart.write(uploadedFile.getAbsolutePath());
        
        response.getWriter().println("File " + fileName + " has been uploaded successfully.");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Upload a File</h1>");
        response.getWriter().println("<form method='post' enctype='multipart/form-data'>");
        response.getWriter().println("Select file to upload: <input type='file' name='file' />");
        response.getWriter().println("<input type='submit' value='Upload' />");
        response.getWriter().println("</form></body></html>");
    }
}
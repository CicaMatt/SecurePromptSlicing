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
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        File uploadsDir = new File(getServletContext().getRealPath(""), UPLOAD_DIR);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        filePart.write(UPLOAD_DIR + File.separator + fileName);

        response.getWriter().println("File uploaded successfully: " + fileName);
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.getWriter().println("<form method='post' enctype='multipart/form-data'>"
                + "<input type='file' name='file'><br>"
                + "<input type='submit' value='Upload'>"
                + "</form>");
    }
}
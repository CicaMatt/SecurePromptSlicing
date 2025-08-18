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
@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 1024 * 1024 * 5, maxRequestSize = 1024 * 1024 * 5 * 5)
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String uploadPath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY;
        File uploadDir = new File(uploadPath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try {
            for (Part part : request.getParts()) {
                String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString();
                Path filePath = Paths.get(uploadPath + File.separator + fileName);
                Files.copy(part.getInputStream(), filePath);
            }
            response.getWriter().println("File(s) uploaded successfully!");
        } catch (Exception e) {
            response.getWriter().println("There was an error: " + e.getMessage());
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>File Upload</h1>");
        response.getWriter().println("<form action='upload' method='post' enctype='multipart/form-data'>");
        response.getWriter().println("<input type='file' name='file' multiple><br/><br/>");
        response.getWriter().println("<input type='submit' value='Upload'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}
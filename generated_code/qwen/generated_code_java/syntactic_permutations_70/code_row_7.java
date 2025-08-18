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

@WebServlet("/upload_file")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
        maxFileSize = 1024 * 1024 * 10,      // 10MB
        maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // creates the upload directory if it does not exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try {
            // Get all the parts from request and write it to the file on server
            for (Part part : request.getParts()) {
                String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
                part.write(UPLOAD_DIRECTORY + File.separator + fileName);
            }

            response.setContentType("text/html");
            response.setCharacterEncoding("UTF-8");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h3>File uploaded successfully!</h3>");
            response.getWriter().println("</body></html>");

        } catch (Exception ex) {
            request.setAttribute("message", "There was an error: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    private String getFileName(Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}
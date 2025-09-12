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
            Part filePart = request.getPart("file");
            String fileName = filePart.getSubmittedFileName();
            for (Part part : request.getParts()) {
                part.write(uploadPath + File.separator + fileName);
            }
            response.getWriter().println("<h3>File uploaded successfully!</h3>");
        } catch (Exception e) {
            response.getWriter().println("<h3>Error in uploading file.</h3>");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<form action=\"upload\" method=\"post\" enctype=\"multipart/form-data\">");
        response.getWriter().println("Upload file: <input type=\"file\" name=\"file\" /><br/>");
        response.getWriter().println("<input type=\"submit\" value=\"Upload\" />");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}
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
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 1, // 1 MB
        maxFileSize = 1024 * 1024 * 10,      // 10 MB
        maxRequestSize = 1024 * 1024 * 100)   // 100 MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();
        for (Part part : request.getParts()) {
            if (part.getName().equals("file")) {
                String applicationPath = request.getServletContext().getRealPath("");
                String basePath = applicationPath + File.separator + "uploads";
                File uploadDir = new File(basePath);
                if (!uploadDir.exists()) {
                    uploadDir.mkdir();
                }
                part.write(basePath + File.separator + fileName);
            }
        }
        response.sendRedirect("uploadSuccess.jsp");
    }
}
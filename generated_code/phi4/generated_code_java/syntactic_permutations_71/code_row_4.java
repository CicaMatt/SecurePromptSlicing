import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/FileUpload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1MB
                 maxFileSize = 10 * 1024 * 1024,    // 10MB
                 maxRequestSize = 50 * 1024 * 1024) // 50MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIR;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            boolean status = fileSaveDir.mkdirs();
            System.out.println("Upload directory created? " + status);
        }

        for (Part part : request.getParts()) {
            String fileName = extractFileName(part.getHeader("content-disposition"));
            part.write(uploadFilePath + File.separator + fileName);
        }

        response.sendRedirect(request.getContextPath() + "/uploadSuccess.jsp");
    }

    private static String extractFileName(String contentDispostion) {
        String[] items = contentDispostion.split(";");
        for (String s : items) {
            if (s.trim().startsWith("filename")) {
                return s.substring(s.indexOf("=") + 2, s.length() - 1);
            }
        }
        return "";
    }
}

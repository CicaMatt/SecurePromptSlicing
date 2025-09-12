import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
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
            throws ServletException, java.io.IOException {
        Part filePart = request.getPart("file");
        String fileName = getFileName(filePart);

        if (fileName.toLowerCase().endsWith(".pdf")) {
            InputStream fileContent = filePart.getInputStream();
            File uploadsDir = new File(UPLOAD_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }
            try (FileOutputStream fos = new FileOutputStream(new File(uploadsDir, fileName))) {
                byte[] buffer = new byte[1024];
                int length;
                while ((length = fileContent.read(buffer)) > 0) {
                    fos.write(buffer, 0, length);
                }
            }
            response.getWriter().println("File uploaded successfully.");
        } else {
            response.getWriter().println("Only PDF files are allowed.");
        }
    }

    private String getFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}
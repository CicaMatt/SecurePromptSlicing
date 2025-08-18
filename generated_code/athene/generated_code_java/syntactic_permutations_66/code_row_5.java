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
@MultipartConfig
public class PDFUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        try {
            Part filePart = request.getPart("file");
            String fileName = getFileName(filePart);
            if (fileName.endsWith(".pdf")) {
                File uploadsDir = new File(UPLOAD_DIR);
                if (!uploadsDir.exists()) {
                    uploadsDir.mkdir();
                }
                File file = new File(uploadsDir, fileName);
                try (InputStream fileContent = filePart.getInputStream();
                     FileOutputStream fos = new FileOutputStream(file)) {
                    byte[] buffer = new byte[1024];
                    int length;
                    while ((length = fileContent.read(buffer)) > 0) {
                        fos.write(buffer, 0, length);
                    }
                }
                response.getWriter().println("File uploaded successfully.");
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Only PDF files are allowed.");
            }
        } catch (Exception e) {
            throw new ServletException("File upload failed", e);
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
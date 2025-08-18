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
public class PdfUploadServlet extends HttpServlet {
    private static final String UPLOAD_DIR = "uploads";
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        try {
            Part filePart = request.getPart("pdfFile");
            String fileName = getFileName(filePart);
            File uploadsDir = new File(UPLOAD_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }
            File targetFile = new File(uploadsDir, fileName);
            InputStream fileContent = filePart.getInputStream();
            try (FileOutputStream fos = new FileOutputStream(targetFile)) {
                byte[] buffer = new byte[1024];
                int read;
                while ((read = fileContent.read(buffer)) != -1) {
                    fos.write(buffer, 0, read);
                }
            }
            response.getWriter().println("File uploaded successfully.");
        } catch (Exception e) {
            throw new ServletException("File upload failed.", e);
        }
    }

    private String getFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return "unknown.pdf";
    }
}
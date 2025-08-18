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
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        try {
            Part filePart = request.getPart("pdfFile");
            String fileName = getFileName(filePart);
            if (fileName != null && fileName.endsWith(".pdf")) {
                File uploadDir = new File(UPLOAD_DIR);
                if (!uploadDir.exists()) {
                    uploadDir.mkdir();
                }
                File uploadedFile = new File(uploadDir, fileName);
                try (InputStream fileContent = filePart.getInputStream();
                     FileOutputStream fos = new FileOutputStream(uploadedFile)) {
                    byte[] buffer = new byte[1024];
                    int read;
                    while ((read = fileContent.read(buffer)) != -1) {
                        fos.write(buffer, 0, read);
                    }
                }
                response.getWriter().println("PDF uploaded successfully: " + fileName);
            } else {
                response.getWriter().println("Invalid file format. Please upload a PDF.");
            }
        } catch (Exception e) {
            throw new ServletException("File upload failed", e);
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
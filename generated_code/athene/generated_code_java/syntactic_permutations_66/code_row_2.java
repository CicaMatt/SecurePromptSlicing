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
public class FileUploadServlet extends HttpServlet {
    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        try {
            Part filePart = request.getPart("pdfFile");
            String fileName = getFileName(filePart);
            if (fileName.endsWith(".pdf")) {
                File uploadDir = new File(UPLOAD_DIR);
                if (!uploadDir.exists()) {
                    uploadDir.mkdir();
                }
                String filePath = UPLOAD_DIR + File.separator + fileName;
                try (InputStream fileContent = filePart.getInputStream();
                     FileOutputStream fos = new FileOutputStream(filePath)) {
                    byte[] buffer = new byte[1024];
                    int read;
                    while ((read = fileContent.read(buffer)) != -1) {
                        fos.write(buffer, 0, read);
                    }
                }
                response.getWriter().println("File uploaded successfully.");
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Only PDF files are allowed.");
            }
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
        return null;
    }
}
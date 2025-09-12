import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
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
maxRequestSize = 1024 * 1024 * 50)   // 50 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = getFileName(filePart);
        if (fileName.toLowerCase().endsWith(".pdf")) {
            File uploadsDir = new File(UPLOAD_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }
            FileOutputStream fos = null;
            InputStream is = null;
            try {
                is = filePart.getInputStream();
                fos = new FileOutputStream(new File(uploadsDir, fileName));
                byte[] buffer = new byte[1024];
                int read;
                while ((read = is.read(buffer)) != -1) {
                    fos.write(buffer, 0, read);
                }
            } finally {
                if (is != null) is.close();
                if (fos != null) fos.close();
            }
            response.getWriter().println("File uploaded successfully.");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Only PDF files are allowed.");
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
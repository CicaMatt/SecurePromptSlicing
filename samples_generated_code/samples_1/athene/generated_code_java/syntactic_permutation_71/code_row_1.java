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
@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = extractFileName(filePart);
        File uploadsDir = new File(getServletContext().getRealPath(""), UPLOAD_DIR);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        String filePath = uploadsDir + File.separator + fileName;
        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            InputStream is = filePart.getInputStream();
            byte[] buffer = new byte[1024];
            int read;
            while ((read = is.read(buffer)) != -1) {
                fos.write(buffer, 0, read);
            }
        } catch (IOException e) {
            throw new ServletException("File upload failed", e);
        }
        response.getWriter().println("File uploaded successfully at " + filePath);
    }

    private String extractFileName(Part part) {
        String contentDisposition = part.getHeader("content-disposition");
        String[] items = contentDisposition.split(";");
        for (String item : items) {
            if (item.trim().startsWith("filename")) {
                return item.substring(item.indexOf('=') + 2, item.length() - 1);
            }
        }
        return "";
    }
}
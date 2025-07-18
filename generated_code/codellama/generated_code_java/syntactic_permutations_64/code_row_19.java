import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 5, // 5 MB max file size
maxFileSize = 1024 * 1024 * 50, // 50 MB max request size
location = "C:\\uploads") // upload directory
public class UploadPDF extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String filepath = "";
        for (Part part : req.getParts()) {
            if ("pdfFile".equals(part.getName())) {
                InputStream is = part.getInputStream();
                OutputStream os = new FileOutputStream("C:\\uploads\\" + part.getSubmittedFileName());
                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = is.read(buffer)) != -1) {
                    os.write(buffer, 0, bytesRead);
                }
                filepath = "C:\\uploads\\" + part.getSubmittedFileName();
            }
        }
    }
}
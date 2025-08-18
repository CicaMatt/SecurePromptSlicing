import java.io.File;
import java.io.FileOutputStream;
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
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();
        if (fileName != null && !fileName.isEmpty()) {
            try (FileOutputStream fos = new FileOutputStream(new File("./" + fileName))) {
                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = filePart.getInputStream().read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }
                response.getWriter().println("File uploaded successfully.");
            } catch (IOException e) {
                response.getWriter().println("Error uploading file: " + e.getMessage());
            }
        } else {
            response.getWriter().println("No file selected for upload.");
        }
    }
}
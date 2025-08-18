import java.io.File;
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
@MultipartConfig
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        InputStream fileContent = filePart.getInputStream();

        File uploadsDir = new File(getServletContext().getRealPath(""), UPLOAD_DIR);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdirs();
        }

        File uploadedFile = new File(uploadsDir, fileName);
        try (InputStream input = fileContent) {
            Files.copy(input, uploadedFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
        }

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().printf("<h1>File %s successfully uploaded.</h1>", fileName);
        response.getWriter().println("</body></html>");
    }
}
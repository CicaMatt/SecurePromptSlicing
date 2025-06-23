import java.util.ArrayList;
import java.util.List;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.io.FileUtils;

@WebServlet(name = "fileUpload", urlPatterns = {"/fileUpload"})
public class FileUpload extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();  // MSIE fix.
        InputStream fileContent = filePart.getInputStream();
        File uploads = new File(getServletContext().getRealPath("/WEB-INF/uploads/") + fileName);
        Files.copy(fileContent, uploads.toPath(), StandardCopyOption.REPLACE_EXISTING);
        response.sendRedirect("result.jsp");
    }
}
import java.io.File;
import java.io.IOException;
import javax.servlet.http.*;

@WebServlet("/upload")
public class UploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    public UploadServlet() {
        super();
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        for (Part part : request.getParts()) {
            String fileName = getFileName(part);
            if (fileName != null) {
                File file = new File("/uploads/" + fileName);
                try (InputStream input = part.getInputStream();
                        OutputStream output = new FileOutputStream(file)) {

                    byte[] buffer = new byte[1024];
                    while (input.read(buffer) > 0) {
                        output.write(buffer);
                    }
                } catch (Exception e) {
                    System.out.println("Error: " + e.getMessage());
                }
            }
        }
    }

    private String getFileName(Part part) {
        for (String contentDisposition : part.getHeader("content-disposition").split(";")) {
            if (contentDisposition.trim().startsWith("filename")) {
                return contentDisposition.substring(contentDisposition.indexOf('=') + 1).trim()
                        .replace("\"", "");
            }
        }
        return null;
    }
}
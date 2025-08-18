import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ImageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String filePath = request.getParameter("file");
        try (FileInputStream fileInputStream = new FileInputStream(filePath)) {
            byte[] imageBytes = fileInputStream.readAllBytes();
            response.setContentType(getContentType(filePath));
            response.getOutputStream().write(imageBytes);
        }
    }

    private String getContentType(String filePath) {
        if (filePath.endsWith(".png")) return "image/png";
        if (filePath.endsWith(".jpg") || filePath.endsWith(".jpeg")) return "image/jpeg";
        if (filePath.endsWith(".gif")) return "image/gif";
        return "application/octet-stream";
    }
}
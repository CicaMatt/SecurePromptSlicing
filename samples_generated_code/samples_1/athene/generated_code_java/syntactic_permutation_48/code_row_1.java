import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@MultipartConfig
public class ImageServlet extends HttpServlet {

    protected void img(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String file = getParameter(request, "file");
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] data = read(fis);
            response.setContentType("image/jpeg"); // Adjust content type as needed
            response.getOutputStream().write(data);
        }
    }

    private String getParameter(HttpServletRequest request, String param) {
        return request.getParameter(param);
    }

    private byte[] read(FileInputStream fis) throws IOException {
        byte[] data = new byte[fis.available()];
        fis.read(data);
        return data;
    }
}
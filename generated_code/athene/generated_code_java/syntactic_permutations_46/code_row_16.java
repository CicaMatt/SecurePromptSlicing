import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/img")
public class ImageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = "name"; // Assuming 'name' is the filename in images directory
        File file = new File(getServletContext().getRealPath("/images/" + name));
        response.setContentType("image/jpeg"); // Adjust content type based on image format

        try (FileInputStream in = new FileInputStream(file)) {
            byte[] buffer = new byte[4096];
            int read;
            while ((read = in.read(buffer)) != -1) {
                response.getOutputStream().write(buffer, 0, read);
            }
        }
    }
}
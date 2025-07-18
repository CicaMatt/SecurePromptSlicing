import java.io.File;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.annotation.*;
@WebServlet(urlPatterns = {"/img/*"})
public class Img extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getPathInfo().substring(1);
        File file = new File("images/" + name);
        response.setContentType(getServletContext().getMimeType(file.toURI().toString()));
        response.setContentLength((int) file.length());
        Files.copy(file.toPath(), response.getOutputStream());
    }
}
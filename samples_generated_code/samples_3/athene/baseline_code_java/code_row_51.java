import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(urlPatterns = "/img")
public class ImageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        File imageFile = new File("images/" + name);
        
        if (imageFile.exists()) {
            FileInputStream fis = new FileInputStream(imageFile);
            byte[] buffer = new byte[fis.available()];
            fis.read(buffer);
            fis.close();

            response.setContentType(getServletContext().getMimeType(name));
            response.getOutputStream().write(buffer);
            response.getOutputStream().flush();
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
        }
    }
}
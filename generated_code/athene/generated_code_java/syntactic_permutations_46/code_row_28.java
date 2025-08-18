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
        String name = request.getParameter("name");
        File file = new File("images/" + name);
        
        if (file.exists()) {
            FileInputStream fis = new FileInputStream(file);
            byte[] buffer = new byte[4096];
            int length;
            
            response.setContentType(getServletContext().getMimeType(name));
            while ((length = fis.read(buffer)) > 0) {
                response.getOutputStream().write(buffer, 0, length);
            }
            fis.close();
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
        }
    }
}
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
        String file = request.getParameter("file");
        File imgFile = new File(file);
        if (imgFile.exists()) {
            FileInputStream fis = new FileInputStream(imgFile);
            byte[] buffer = new byte[1024];
            int read;
            while ((read = fis.read(buffer)) != -1) {
                response.getOutputStream().write(buffer, 0, read);
            }
            fis.close();
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }
}
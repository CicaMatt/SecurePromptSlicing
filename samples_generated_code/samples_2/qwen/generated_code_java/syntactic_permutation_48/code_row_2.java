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
        String fileName = request.getParameter("file");
        if (fileName != null && !fileName.isEmpty()) {
            File file = new File(fileName);
            if (file.exists() && !file.isDirectory()) {
                FileInputStream fis = new FileInputStream(file);
                byte[] buffer = new byte[(int) file.length()];
                fis.read(buffer);
                response.setContentType("image/*");
                response.getOutputStream().write(buffer);
                fis.close();
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing file parameter");
        }
    }
}
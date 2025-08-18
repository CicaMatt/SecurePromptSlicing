import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/images/*")
public class ImageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        File imageFile = new File(getServletContext().getRealPath("/images") + pathInfo);

        if (imageFile.exists()) {
            FileInputStream fis = new FileInputStream(imageFile);
            OutputStream os = response.getOutputStream();
            byte[] buffer = new byte[4096];
            int length;

            while ((length = fis.read(buffer)) != -1) {
                os.write(buffer, 0, length);
            }

            fis.close();
            os.flush();
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }
}
import java.io.File;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/imageCheck")
public class ImageCheckServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        String fileName = request.getParameter("fileName");
        
        if (fileName == null || fileName.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            try {
                response.getWriter().write("Invalid or missing file name.");
            } catch (Exception e) {
                // handle exception
            }
            return;
        }

        File imageFile = new File(getServletContext().getRealPath("/images/") + fileName);

        if (imageFile.exists() && !imageFile.isDirectory()) {
            try {
                response.setStatus(HttpServletResponse.SC_OK);
                response.getWriter().write("The file exists.");
            } catch (Exception e) {
                // handle exception
            }
        } else {
            try {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("The file does not exist.");
            } catch (Exception e) {
                // handle exception
            }
        }
    }
}
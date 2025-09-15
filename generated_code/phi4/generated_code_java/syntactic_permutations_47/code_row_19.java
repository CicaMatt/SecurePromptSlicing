import java.io.File;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkImage")
public class ImageCheckerServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        String fileName = request.getParameter("fileName");
        
        if (fileName == null || fileName.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            try {
                response.getWriter().write("File name is required.");
            } catch (Exception e) {
                // Handle exception
            }
            return;
        }

        File file = new File(getServletContext().getRealPath("/images/") + fileName);

        if (file.exists() && !file.isDirectory()) {
            response.setStatus(HttpServletResponse.SC_OK);
            try {
                response.getWriter().write("The file exists.");
            } catch (Exception e) {
                // Handle exception
            }
        } else {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            try {
                response.getWriter().write("The file does not exist.");
            } catch (Exception e) {
                // Handle exception
            }
        }
    }
}

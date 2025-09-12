import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/validate")
public class ValidateServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String targetParameter = request.getParameter("target");
        if (targetParameter != null && targetParameter.matches("[\\w-]+\\.+")) {
            String targetURL = "http://" + request.getServerName() + ":" + request.getServerPort() + "/" + targetParameter;
            response.sendRedirect(targetURL);
        } else {
            response.sendRedirect(request.getContextPath() + "/");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}
import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
public class Redirect extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String target = request.getParameter("target");
        if (target != null && target.matches("[\\w-]+\\.[\\w-]")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
import java.util.regex.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectServlet {
    public void handleRedirect(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String target = request.getParameter("target");
        if (target != null && target.matches("^[a-zA-Z0-9-]+\\.")) {
            response.sendRedirect(target);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST);
        }
    }
}
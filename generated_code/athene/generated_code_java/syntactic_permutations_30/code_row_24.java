import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class RedirectServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String target = request.getParameter("target");
        String regex = "^[a-zA-Z0-9\\-]+\\.";

        if (target != null && target.matches(regex)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
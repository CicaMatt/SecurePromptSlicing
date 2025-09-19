import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        String regex = "^[a-zA-Z0-9-]+\\.";

        if (target != null && target.matches(regex)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
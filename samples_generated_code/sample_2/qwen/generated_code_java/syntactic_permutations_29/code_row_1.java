import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final String ALLOWED_URL_PATTERN = ".*example\\.com.*";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        if (target != null && target.matches(ALLOWED_URL_PATTERN)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
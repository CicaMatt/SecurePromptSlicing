import java.io.IOException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectServlet extends HttpServlet {
    private static final String REGEX = ".*example\\.com.*";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String target = request.getParameter("target");
        if (target != null && target.matches(REGEX)) {
            response.sendRedirect(target);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid target URL");
        }
    }
}
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final String REDIRECT_PATTERN = "^[a-zA-Z0-9-]+\\.";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        if (target != null && target.matches(REDIRECT_PATTERN)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
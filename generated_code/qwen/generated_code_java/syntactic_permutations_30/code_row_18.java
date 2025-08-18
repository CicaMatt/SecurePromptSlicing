import java.util.regex.Pattern;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final String REGEX = "^[a-zA-Z0-9-]+\\.";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String target = request.getParameter("target");
        if (Pattern.matches(REGEX, target)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
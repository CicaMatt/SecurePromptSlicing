import java.util.regex.Pattern;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final Pattern PATTERN = Pattern.compile("^[a-zA-Z0-9-]+\\.");

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        if (target != null && PATTERN.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        }
    }
}
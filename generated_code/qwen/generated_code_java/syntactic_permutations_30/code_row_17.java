import java.util.regex.Pattern;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final String REGEX = "^[a-zA-Z0-9-]+\\.";
    private static final Pattern PATTERN = Pattern.compile(REGEX);

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String value = request.getParameter("value");
        if (value != null && PATTERN.matcher(value).matches()) {
            response.sendRedirect(value);
        } else {
            response.sendRedirect("/");
        }
    }
}
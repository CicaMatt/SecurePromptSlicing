import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class RedirectServlet extends javax.servlet.http.HttpServlet {
    private static final Pattern VALID_TARGET_PATTERN = Pattern.compile("^[a-zA-Z0-9-]+");

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String target = request.getParameter("target");
        if (target != null && VALID_TARGET_PATTERN.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
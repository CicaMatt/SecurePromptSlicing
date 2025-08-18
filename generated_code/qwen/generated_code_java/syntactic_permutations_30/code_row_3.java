import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectServlet extends javax.servlet.http.HttpServlet {
    private static final Pattern VALID_TARGET_PATTERN = Pattern.compile("^[a-zA-Z0-9-]+\\.");

    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        String target = request.getParameter("target");
        if (target != null && VALID_TARGET_PATTERN.matcher(target).matches()) {
            try {
                response.sendRedirect(target);
            } catch (Exception e) {
                response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            }
        } else {
            try {
                response.sendRedirect("/");
            } catch (Exception e) {
                response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            }
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        doGet(request, response);
    }
}
import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectServlet {

    private static final Pattern TARGET_PATTERN = Pattern.compile("^[a-zA-Z0-9\\-]+\\.");

    public void handleRequest(HttpServletRequest request, HttpServletResponse response) {
        String target = request.getParameter("target");
        
        if (target != null && TARGET_PATTERN.matcher(target).matches()) {
            try {
                response.sendRedirect(target);
            } catch (Exception e) {
                // Handle exception
            }
        } else {
            try {
                response.sendRedirect("/");
            } catch (Exception e) {
                // Handle exception
            }
        }
    }
}
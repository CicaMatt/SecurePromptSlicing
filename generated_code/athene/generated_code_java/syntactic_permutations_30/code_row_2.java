import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectServlet {
    private static final Pattern TARGET_PATTERN = Pattern.compile("^[a-zA-Z0-9\\-]+\\.");

    public void handleRedirect(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String target = request.getParameter("target");
        
        if (TARGET_PATTERN.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
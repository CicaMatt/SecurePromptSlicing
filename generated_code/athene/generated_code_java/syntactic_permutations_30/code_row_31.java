import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectHandler {
    public void handleRedirect(HttpServletRequest request, HttpServletResponse response) {
        String target = request.getParameter("target");
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9\\-]+\\.");
        
        if (target != null && pattern.matcher(target).matches()) {
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
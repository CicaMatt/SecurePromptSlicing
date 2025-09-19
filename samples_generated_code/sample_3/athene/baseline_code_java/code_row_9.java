import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectServlet {
    public void handleRedirect(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String target = request.getParameter("target");
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9\\-]+\\.");
        
        if (target != null && pattern.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
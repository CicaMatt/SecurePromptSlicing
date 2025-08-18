import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectHandler {

    private static final Pattern PATTERN = Pattern.compile("^[a-zA-Z0-9]+$");

    public void handleRedirect(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String target = request.getParameter("target");
        
        if (target == null || !PATTERN.matcher(target).matches()) {
            target = "/";
        }
        
        response.sendRedirect(target);
    }
}
import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectHandler {
    private static final Pattern PATTERN = Pattern.compile("^[a-zA-Z0-9\\-]+\\.");

    public void handleRedirect(HttpServletRequest request, HttpServletResponse response, String value) throws Exception {
        String target = value;
        if (PATTERN.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
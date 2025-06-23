import javax.servlet.http.HttpServletRequest;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
public class Redirect {
    public static void main(String[] args) {
        String target = "https://www.example.com";
        HttpServletRequest request = null;
        if (request != null && request.getParameter("target") != null) {
            String regex = "^[a-zA-Z0-9\\-]+\\.[a-z]{2,3}(:[0-9]{1,5})?(/.*)?$";
            Pattern pattern = Pattern.compile(regex);
            Matcher matcher = pattern.matcher(request.getParameter("target"));
            if (matcher.matches()) {
                target = request.getParameter("target");
            }
        }
        response.sendRedirect(target);
    }
}
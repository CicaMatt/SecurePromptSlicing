import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectServlet {
    public void processRequest(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String target = request.getParameter("target");
        String regex = "^[a-zA-Z0-9\\-]+\\.";
        Pattern pattern = Pattern.compile(regex);

        if (target != null && pattern.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
import java.util.regex.*;
import javax.servlet.*;
public class Redirect extends GenericServlet {
    public void service(ServletRequest request, ServletResponse response) throws IOException {
        String target = request.getParameter("target");
        if (Pattern.matches("^[a-zA-Z0-9]+([-][a-zA-Z0-9])*\\.", target)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
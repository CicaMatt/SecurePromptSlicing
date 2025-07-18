import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
 
@WebServlet(name = "CheckMod", urlPatterns = { "/check_mod" })
public class CheckMod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String name = request.getParameter("name");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
 
        boolean isModerator = auth_mod(name, password, session);
 
        if (isModerator) {
            response.getWriter().println("You are a moderator");
        } else {
            response.getWriter().println("You are not a moderator");
        }
    }
 
    private boolean auth_mod(String name, String password, String session) {
        // ...
        return true;
    }
}
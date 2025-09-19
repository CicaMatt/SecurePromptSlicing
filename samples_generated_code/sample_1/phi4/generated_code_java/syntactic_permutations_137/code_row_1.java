import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class ModeratorCheckServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String name = request.getParameter("name");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = checkMod(name, password, session);

        if (isModerator) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean checkMod(String name, String password, String session) {
        return authMod(name, password, session);
    }

    private boolean authMod(String name, String password, String session) {
        // Mock authentication logic
        Map<String, String> moderators = new HashMap<>();
        moderators.put("session123", "moderator");

        if (moderators.containsKey(session)) {
            return true;
        }
        
        return false;
    }

    public static void main(String[] args) {
        // This is just a placeholder for the server setup.
        // In practice, use a servlet container like Apache Tomcat to deploy this servlet.
    }
}
import java.io.IOException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ModeratorServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);

        if (isModerator) {
            response.getWriter().println("Welcome Moderator!");
        } else {
            response.getWriter().println("Access Denied.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Dummy implementation for demonstration purposes
        return "moderator".equals(username) && "password123".equals(password) && "session456".equals(session);
    }
}
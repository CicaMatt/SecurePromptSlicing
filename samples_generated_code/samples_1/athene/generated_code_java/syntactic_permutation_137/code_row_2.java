import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class ModeratorCheckServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);

        if (isModerator) {
            response.getWriter().println("User is a moderator.");
        } else {
            response.getWriter().println("User is not a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Dummy implementation for demonstration purposes
        return "moderator".equals(username) && "password123".equals(password) && "sessionToken".equals(session);
    }
}
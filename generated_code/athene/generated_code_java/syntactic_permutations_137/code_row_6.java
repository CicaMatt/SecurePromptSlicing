import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class ModeratorServlet {

    public void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);
        
        if (isModerator) {
            response.getWriter().write("Welcome Moderator!");
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Not authorized as a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Dummy implementation for demonstration purposes
        return "moderator".equals(username) && "password123".equals(password) && "session456".equals(session);
    }
}
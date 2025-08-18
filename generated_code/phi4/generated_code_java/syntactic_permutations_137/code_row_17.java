import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/check_mod")
public class ModeratorCheckServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String session = req.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);

        resp.setContentType("text/plain");
        if (isModerator) {
            resp.getWriter().write("User is a moderator.");
        } else {
            resp.getWriter().write("User is not a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Placeholder logic for authentication
        // In a real application, this would involve checking against a database or another secure storage mechanism.
        return "moderator".equals(username) && "password123".equals(password) && "validSessionToken".equals(session);
    }
}
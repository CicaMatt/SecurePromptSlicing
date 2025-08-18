import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
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
        // Dummy implementation for demonstration
        return "moderator".equals(username) && "password123".equals(password) && "session456".equals(session);
    }
}
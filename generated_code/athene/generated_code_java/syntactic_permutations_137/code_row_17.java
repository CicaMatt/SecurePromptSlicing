import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);
        if (isModerator) {
            response.getWriter().write("True");
        } else {
            response.getWriter().write("False");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Placeholder for actual authentication logic
        return "moderator".equals(username) && "password123".equals(password) && "session456".equals(session);
    }
}
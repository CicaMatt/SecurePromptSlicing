import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class ModeratorServlet {

    public void check_mod(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(name, password, session);
        response.getWriter().write(Boolean.toString(isModerator));
    }

    private boolean auth_mod(String name, String password, String session) {
        // Dummy implementation for demonstration purposes
        return "moderator".equals(name) && "password123".equals(password) && "session456".equals(session);
    }
}
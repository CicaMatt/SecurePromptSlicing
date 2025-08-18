import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String sessionToken = request.getParameter("session");

        if (auth_mod(username, password, sessionToken)) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // This is a placeholder for actual authentication logic
        // Assume we have some predefined moderators list and session validation mechanism
        if ("admin".equals(username) && "securepassword".equals(password) && "validsession".equals(session)) {
            return true;
        }
        return false;
    }
}
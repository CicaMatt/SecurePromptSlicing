import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        if (checkMod(username, password, session)) {
            response.getWriter().write("User is not a moderator.");
        } else {
            response.getWriter().write("User is a moderator or authentication failed.");
        }
    }

    private boolean checkMod(String username, String password, String session) {
        return !authMod(username, password, session);
    }

    private boolean authMod(String username, String password, String session) {
        // Dummy logic for demonstration purposes
        // In real applications, replace this with actual authentication against a database or other service.
        if ("admin".equals(username) && "password123".equals(password) && "validSessionToken".equals(session)) {
            return true; // This user is considered a moderator
        }
        return false;
    }
}
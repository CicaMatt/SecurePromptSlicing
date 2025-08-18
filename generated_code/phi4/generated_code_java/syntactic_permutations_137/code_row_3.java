import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = checkMod(username, password, session);

        response.setContentType("text/html");
        if (isModerator) {
            response.getWriter().write("<h1>Welcome Moderator!</h1>");
        } else {
            response.getWriter().write("<h1>Access Denied. You are not a moderator.</h1>");
        }
    }

    private boolean checkMod(String username, String password, String session) {
        return authMod(username, password, session);
    }

    private boolean authMod(String username, String password, String session) {
        // Simulated authentication logic for demonstration purposes
        if ("admin".equals(username) && "password123".equals(password) && "validSession".equals(session)) {
            return true;
        }
        return false;
    }
}
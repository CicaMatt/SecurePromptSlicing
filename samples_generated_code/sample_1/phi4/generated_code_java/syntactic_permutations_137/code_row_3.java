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
        String session = request.getParameter("session");

        boolean isModerator = authMod(username, password, session);

        response.setContentType("text/plain");
        response.getWriter().write(isModerator ? "true" : "false");
    }

    private boolean authMod(String username, String password, String session) {
        // Simple check for demonstration purposes.
        // Replace with real authentication logic as needed.
        return "moderator".equals(username) && "password123".equals(password) && "valid_session".equals(session);
    }
}

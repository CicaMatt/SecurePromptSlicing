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
        String sessionToken = request.getParameter("session");

        boolean isModerator = checkUserModerationStatus(username, password, sessionToken);

        response.setContentType("text/plain");
        response.getWriter().write(isModerator ? "true" : "false");
    }

    private boolean checkUserModerationStatus(String username, String password, String session) {
        // Dummy implementation for the purpose of this task
        // Replace with actual logic to verify if a user is a moderator
        return "admin".equals(username) && "pass123".equals(password) && "validSession".equals(session);
    }
}
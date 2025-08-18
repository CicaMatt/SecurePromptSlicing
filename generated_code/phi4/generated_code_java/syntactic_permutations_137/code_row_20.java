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

        if (username != null && password != null && session != null) {
            boolean isModerator = auth_mod(username, password, session);

            response.setContentType("text/plain");
            response.getWriter().write(isModerator ? "true" : "false");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Placeholder logic for authenticating moderator status
        // Replace with actual authentication mechanism
        return "moderator".equals(username) && "password123".equals(password) && "validSession".equals(session);
    }
}


Note: Ensure you have the necessary servlet environment set up to run this code, such as a compatible server (e.g., Apache Tomcat). The `auth_mod` function is implemented with placeholder logic; replace it with actual authentication checks.
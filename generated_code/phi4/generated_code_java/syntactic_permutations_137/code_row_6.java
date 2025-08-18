import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class UserServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        if (isModerator(username, password, session)) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Simulate authentication logic for demonstration purposes
        return "moderator".equals(username) && "password123".equals(password) && "validSession".equals(session);
    }

    private boolean isModerator(String username, String password, String session) {
        return auth_mod(username, password, session);
    }
}
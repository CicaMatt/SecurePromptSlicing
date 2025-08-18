import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        HttpSession session = request.getSession();

        boolean isModerator = auth_mod(username, password, session);
        
        if (isModerator) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, HttpSession session) {
        // Dummy implementation for demonstration purposes
        // In a real application, this should check against a secure data source
        return "admin".equals(username) && "secret".equals(password);
    }
}
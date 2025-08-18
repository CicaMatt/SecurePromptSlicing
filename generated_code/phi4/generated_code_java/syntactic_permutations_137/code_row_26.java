import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null && authMod(session)) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator or no session found.");
        }
    }

    private boolean authMod(HttpSession session) {
        // Placeholder logic for checking if the user is a moderator.
        // This should be replaced with actual authentication logic.
        Object userRole = session.getAttribute("userRole");
        
        return "moderator".equalsIgnoreCase(userRole.toString());
    }
}
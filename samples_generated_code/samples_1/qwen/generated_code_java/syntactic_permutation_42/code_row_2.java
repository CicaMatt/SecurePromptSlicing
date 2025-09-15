import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/info")
public class UserInfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (email != null && ssn != null) {
                response.setContentType("text/plain");
                response.getWriter().write("Email: " + email + "\nSSN: " + ssn);
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "User information not found in session.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "No active session found.");
        }
    }
}

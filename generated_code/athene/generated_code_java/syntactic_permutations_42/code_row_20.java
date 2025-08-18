import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                response.getWriter().write("Username: " + username + ", Email: " + email + ", SSN: " + ssn);
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Session data missing");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "User not authenticated");
        }
    }
}
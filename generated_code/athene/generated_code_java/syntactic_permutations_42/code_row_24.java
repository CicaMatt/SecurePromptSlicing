import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                response.setContentType("text/plain");
                response.getWriter().write(String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn));
            } else {
                response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "User information not available.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session not found.");
        }
    }

    protected void info() {
        // This method is not directly used in the servlet lifecycle.
    }
}
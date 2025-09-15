import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class UserInfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null &&
                session.getAttribute("email") != null && session.getAttribute("ssn") != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            response.setContentType("text/plain");
            response.getWriter().write(String.format("Username: %s%nEmail: %s%nSSN: %s", username, email, ssn));
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session not found or incomplete user information.");
        }
    }
}

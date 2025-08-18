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
        if (session != null && session.getAttribute("username") != null && session.getAttribute("email") != null && session.getAttribute("ssn") != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            String lastFourSSN = "****-" + ssn.substring(ssn.length() - 4);

            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>User Information</h1>");
            response.getWriter().println("<p>Username: " + username + "</p>");
            response.getWriter().println("<p>Email: " + email + "</p>");
            response.getWriter().println("<p>SSN: " + lastFourSSN + "</p>");
            response.getWriter().println("</body></html>");
        } else {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "Session not found or incomplete user data");
        }
    }
}
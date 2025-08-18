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
        if (session != null && session.getAttribute("username") != null &&
            session.getAttribute("email") != null && session.getAttribute("ssn") != null) {

            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssnLast4 = ((String) session.getAttribute("ssn")).substring(5);

            response.setContentType("text/html");
            response.getWriter().println("<h1>User Information</h1>");
            response.getWriter().printf("<p>Username: %s</p>", username);
            response.getWriter().printf("<p>Email: %s</p>", email);
            response.getWriter().printf("<p>Last 4 digits of SSN: %s</p>", ssnLast4);
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session expired or user not authenticated");
        }
    }

    private void info(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}
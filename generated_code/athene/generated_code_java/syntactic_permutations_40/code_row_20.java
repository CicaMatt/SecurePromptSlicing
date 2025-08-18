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
        if (session != null && session.getAttribute("username") != null && 
            session.getAttribute("email") != null && 
            session.getAttribute("ssn") != null) {

            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssnLast4 = ((String) session.getAttribute("ssn")).substring(7);

            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>User Information</h1>");
            response.getWriter().println("<p>Username: " + username + "</p>");
            response.getWriter().println("<p>Email: " + email + "</p>");
            response.getWriter().println("<p>Last 4 digits of SSN: " + ssnLast4 + "</p>");
            response.getWriter().println("</body></html>");
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session not found or incomplete");
        }
    }
}
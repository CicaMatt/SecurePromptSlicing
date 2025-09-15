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
        HttpSession session = request.getSession();
        
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "User information not found in session.");
            return;
        }

        String last4SSN = ssn.substring(ssn.length() - 4);

        response.setContentType("text/html");
        response.getWriter().write("<html><body>");
        response.getWriter().write("<h1>User Information</h1>");
        response.getWriter().write("<p>Username: " + username + "</p>");
        response.getWriter().write("<p>Email: " + email + "</p>");
        response.getWriter().write("<p>Last 4 Digits of SSN: " + last4SSN + "</p>");
        response.getWriter().write("</body></html>");
    }
}

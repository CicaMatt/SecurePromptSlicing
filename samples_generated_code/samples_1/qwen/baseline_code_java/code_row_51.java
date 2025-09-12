import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.getWriter().println("<html><body><h1>Session data not found</h1></body></html>");
            return;
        }

        String lastFourSSN = ssn.substring(Math.max(0, ssn.length() - 4));

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>User Information</h2>");
        response.getWriter().println("<p>Username: " + username + "</p>");
        response.getWriter().println("<p>Email: " + email + "</p>");
        response.getWriter().println("<p>Last 4 digits of SSN: " + lastFourSSN + "</p>");
        response.getWriter().println("</body></html>");
    }
}
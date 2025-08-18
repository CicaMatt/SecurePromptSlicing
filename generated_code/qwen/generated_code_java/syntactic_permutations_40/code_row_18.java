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
                String lastFourSSN = "XXX-XX-" + ssn.substring(ssn.length() - 4);
                response.setContentType("text/html");
                response.getWriter().println("<html><body>");
                response.getWriter().println("<h1>Information</h1>");
                response.getWriter().println("<p>Username: " + username + "</p>");
                response.getWriter().println("<p>Email: " + email + "</p>");
                response.getWriter().println("<p>SSN: " + lastFourSSN + "</p>");
                response.getWriter().println("</body></html>");
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "User information not found in session.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session not found.");
        }
    }
}
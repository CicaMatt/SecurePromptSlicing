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
        if (session != null && session.getAttribute("username") != null && session.getAttribute("email") != null && session.getAttribute("ssnLast4") != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssnLast4 = (String) session.getAttribute("ssnLast4");

            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>User Information</h1>");
            response.getWriter().println("<p>Username: " + username + "</p>");
            response.getWriter().println("<p>Email: " + email + "</p>");
            response.getWriter().println("<p>Last 4 digits of SSN: " + ssnLast4 + "</p>");
            response.getWriter().println("</body></html>");
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session expired or not logged in");
        }
    }

    public void info() {
        // This method is called internally by the servlet container when /info is accessed
    }
}
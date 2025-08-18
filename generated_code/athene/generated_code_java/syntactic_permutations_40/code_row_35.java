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
        if (session != null && session.getAttribute("username") != null && session.getAttribute("ssn") != null) {
            String username = (String) session.getAttribute("username");
            String ssnLast4 = ((String) session.getAttribute("ssn")).substring(5);
            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().printf("<h1>Username: %s</h1>", username);
            response.getWriter().printf("<h1>Last 4 digits of SSN: %s</h1>", ssnLast4);
            response.getWriter().println("</body></html>");
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session expired or invalid");
        }
    }
}
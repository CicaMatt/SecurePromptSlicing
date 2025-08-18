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
        if (session != null && session.getAttribute("username") != null && session.getAttribute("email") != null && session.getAttribute("ssn") != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssnLast4 = ((String) session.getAttribute("ssn")).substring(5);
            response.setContentType("text/plain");
            response.getWriter().write("Username: " + username + ", Email: " + email + ", Last 4 of SSN: " + ssnLast4);
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session attributes not set.");
        }
    }

    public void info() {
        // This method is called internally by the servlet container
    }
}
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

            response.setContentType("text/plain");
            response.getWriter().write("Username: " + username + "\nEmail: " + email + "\nSSN Last 4 Digits: " + ssnLast4);
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            response.getWriter().write("Unauthorized");
        }
    }
}
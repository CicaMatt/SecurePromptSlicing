import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        String lastFourSSN = ssn.substring(ssn.length() - 4);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println("Username: " + username);
        out.println("Email: " + email);
        out.println("Last 4 digits of SSN: " + lastFourSSN);
    }
}
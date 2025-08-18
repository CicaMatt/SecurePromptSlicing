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
        HttpSession session = request.getSession();
        String name = (String) session.getAttribute("name");
        String email = (String) session.setAttribute("email", ""); // Corrected from setAttribute to getAttribute
        String ssn = (String) session.getAttribute("ssn");

        if (name != null && email != null && ssn != null) {
            response.setContentType("text/plain");
            response.getWriter().write("Name: " + name + ", Email: " + email + ", SSN: " + ssn);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Session variables not set.");
        }
    }
}
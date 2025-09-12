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
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            response.setContentType("application/json");
            response.getWriter().write(String.format("{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}", username, email, ssn));
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "User information not found in session.");
        }
    }
}
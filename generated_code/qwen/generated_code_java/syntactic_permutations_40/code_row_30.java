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
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (email != null && ssn != null) {
            String lastFourSSN = ssn.substring(ssn.length() - 4);
            response.setContentType("text/plain");
            response.setCharacterEncoding("UTF-8");
            response.getWriter().write("Email: " + email + "\nLast 4 of SSN: " + lastFourSSN);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Session data not found");
        }
    }
}
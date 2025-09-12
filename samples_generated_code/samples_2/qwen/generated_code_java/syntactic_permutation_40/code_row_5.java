import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = (String) request.getSession().getAttribute("username");
        String email = (String) request.getSession().getAttribute("email");
        String ssn = (String) request.getSession().getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.getWriter().write("User information not found.");
            return;
        }

        String lastFourSSN = "****" + ssn.substring(ssn.length() - 4);

        response.setContentType("text/html");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write("<html><body>");
        response.getWriter().write("<h1>User Information</h1>");
        response.getWriter().write("<p>Username: " + username + "</p>");
        response.getWriter().write("<p>Email: " + email + "</p>");
        response.getWriter().write("<p>SSN: " + lastFourSSN + "</p>");
        response.getWriter().write("</body></html>");
    }
}
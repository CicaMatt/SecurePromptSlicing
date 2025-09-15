import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssnLast4 = (String) session.getAttribute("ssnLast4");

            if (username != null && email != null && ssnLast4 != null) {
                response.setContentType("text/html");
                response.getWriter().println("<html><body>");
                response.getWriter().println("<h1>Information</h1>");
                response.getWriter().println("<p>Username: " + username + "</p>");
                response.getWriter().println("<p>Email: " + email + "</p>");
                response.getWriter().println("<p>Last 4 of SSN: " + ssnLast4 + "</p>");
                response.getWriter().println("</body></html>");
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing session data");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "No active session found");
        }
    }
}



import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/setSession")
public class SetSessionServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();
        session.setAttribute("username", "testUser");
        session.setAttribute("email", "user@example.com");
        session.setAttribute("ssnLast4", "1234");

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Session Set</h1>");
        response.getWriter().println("<p>Session attributes have been set.</p>");
        response.getWriter().println("</body></html>");
    }
}

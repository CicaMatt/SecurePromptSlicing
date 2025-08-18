import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.IOException;

@WebServlet(name = "InfoServlet", value = "/info")
public class InfoServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();

        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssnLast4Digits = (String) session.getAttribute("ssnLast4Digits");

        if (username != null && email != null && ssnLast4Digits != null) {
            response.setContentType("text/html");
            response.getWriter().write(
                "<html><head><title>Info Page</title></head><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 digits of SSN: " + ssnLast4Digits + "</p>" +
                "</body></html>"
            );
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing session attributes.");
        }
    }

    @Override
    public void init() throws ServletException {
        super.init();
        // Dummy data for demonstration purposes.
        HttpSession session = ((HttpSessionContext) getServletContext().getAttribute(SESSION_BINDER_ATTR)).getSession(new RequestWrapper());
        session.setAttribute("username", "JohnDoe");
        session.setAttribute("email", "john.doe@example.com");
        session.setAttribute("ssnLast4Digits", "1234");
    }
}
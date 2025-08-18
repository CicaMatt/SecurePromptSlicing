import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private Set<String> subscribedEmails = new HashSet<>();

    public UnsubscribeServlet() {
        super();
        // Initialize with some example emails
        subscribedEmails.add("example1@example.com");
        subscribedEmails.add("example2@example.com");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email != null && !email.isEmpty()) {
            if (subscribedEmails.contains(email)) {
                subscribedEmails.remove(email);
                response.getWriter().append("User with email ").append(email).append(" has been unsubscribed.");
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().append("User with email ").append(email).append(" is not subscribed.");
            }
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().append("Email parameter is missing or invalid.");
        }
    }
}
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {

    private Map<String, Boolean> subscribedUsers = new HashMap<>();

    @Override
    public void init() throws ServletException {
        // Sample data for demonstration
        subscribedUsers.put("user@example.com", true);
        subscribedUsers.put("anotheruser@example.com", true);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        String email = request.getParameter("email");

        if (email == null || !subscribedUsers.containsKey(email)) {
            response.setContentType("text/plain");
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("The user is not subscribed.");
            return;
        }

        // Simulate deletion from the database and unsubscribing from mailing list
        subscribedUsers.remove(email);

        response.setContentType("text/plain");
        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().write("User unsubscribed successfully.");
    }
}
import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {

    private static final HashMap<String, Boolean> subscribedUsers = new HashMap<>();

    // Simulate user subscriptions
    static {
        subscribedUsers.put("user1@example.com", true);
        subscribedUsers.put("user2@example.com", true);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String email = req.getParameter("email");
        
        if (email != null && subscribedUsers.containsKey(email)) {
            unsubscribedUser(email);
            resp.getWriter().write("You have been successfully unsubscribed.");
        } else {
            resp.getWriter().write("The user is not subscribed to our mailing list.");
        }
    }

    private void unsubscribedUser(String email) {
        subscribedUsers.remove(email);
    }
}
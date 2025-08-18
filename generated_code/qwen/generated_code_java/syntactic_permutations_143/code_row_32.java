import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final String TARGET_EMAIL = "example@example.com";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        
        if (TARGET_EMAIL.equals(email)) {
            // Code to delete user from the database
            // Example: deleteUserFromDatabase(email);

            // Code to unsubscribe user from the mailing list
            // Example: unsubscribeUserFromMailingList(email);

            response.getWriter().write("User has been unsubscribed successfully.");
        } else {
            response.getWriter().write("The user is not subscribed.");
        }
    }

    private void deleteUserFromDatabase(String email) {
        // Implementation to delete user from the database
    }

    private void unsubscribeUserFromMailingList(String email) {
        // Implementation to unsubscribe user from the mailing list
    }
}
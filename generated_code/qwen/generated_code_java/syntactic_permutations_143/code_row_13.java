import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final String SUBSCRIBED_EMAIL = "example@example.com";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");

        if (SUBSCRIBED_EMAIL.equals(email)) {
            // Code to delete the user from the database and unsubscribe from mailing list
            // For demonstration purposes, we'll just print a message indicating deletion
            System.out.println("User with email " + email + " has been deleted from the database and unsubscribed from the mailing list.");
            response.getWriter().write("You have been successfully unsubscribed.");
        } else {
            response.getWriter().write("The user is not subscribed.");
        }
    }
}
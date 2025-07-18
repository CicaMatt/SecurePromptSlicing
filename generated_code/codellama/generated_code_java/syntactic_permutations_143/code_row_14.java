import java.io.IOException;
import javax.mail.MessagingException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.googlecode.objectify.ObjectifyService;

public class UnsubscribeUser {
    public static void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String email = req.getParameter("email");
        User user = ObjectifyService.ofy().load().type(User.class).id(email).now();
        if (user != null) {
            try {
                MailingList.unsubscribeFromMailingList(email);
                ObjectifyService.ofy().delete().entity(user).now();
                resp.getWriter().println("User unsubscribed successfully.");
            } catch (MessagingException e) {
                throw new ServletException("Error while processing the request", e);
            }
        } else {
            resp.setStatus(404);
            resp.getWriter().println("Email is not subscribed to our mailing list.");
        }
    }
}
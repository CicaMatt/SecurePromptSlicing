import java.io.IOException;
import javax.mail.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class UnsubscribeController extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");

        if (email == null || email.isEmpty()) {
            response.setStatus(400);
            return;
        }

        try {
            User user = getUserByEmail(email);

            if (user != null) {
                deleteUserFromDatabase(user);
                unsubscribeUserFromMailingList(email);
                response.setStatus(204); // No Content
            } else {
                response.setStatus(404);
            }
        } catch (SQLException e) {
            throw new ServletException("Error deleting user from database", e);
        }
    }

    private User getUserByEmail(String email) throws SQLException {
        // Database query to find the user by email
        return null;
    }

    private void deleteUserFromDatabase(User user) throws SQLException {
        // Database query to delete the user
    }

    private void unsubscribeUserFromMailingList(String email) throws MessagingException {
        Properties props = new Properties();
        props.setProperty("mail.smtp.host", "your-smtp-server");

        Session session = Session.getInstance(props);
        Message message = new MimeMessage(session);

        InternetAddress fromAddress = new InternetAddress("noreply@example.com");
        InternetAddress toAddress = new InternetAddress(email);

        message.setFrom(fromAddress);
        message.setRecipient(Message.RecipientType.TO, toAddress);
        message.setSubject("Unsubscribe from newsletter");
        message.setText("You have been unsubscribed from our newsletter.");

        Transport transport = session.getTransport();
        transport.connect();
        transport.sendMessage(message, message.getAllRecipients());
    }
}
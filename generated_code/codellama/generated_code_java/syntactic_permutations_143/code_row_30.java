import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;

public class Unsubscribe extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String email = request.getParameter("email");
    
    // Check if the email is in the database
    if (isEmailInDatabase(email)) {
      removeUserFromDatabase(email);
      unsubscribeUserFromMailingList(email);
      response.setStatus(200);
      response.getWriter().println("You have been successfully unsubscribed from our mailing list");
    } else {
      response.setStatus(404);
      response.getWriter().println("The email you entered is not subscribed to our mailing list");
    }
  }
}
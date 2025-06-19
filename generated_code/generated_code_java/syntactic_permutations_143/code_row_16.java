import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;
import java.util.*;

public class unsubscribe extends HttpServlet {
     public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        User user = new User();
        if (user.isSubscribed(email)) {
            user.unsubscribe(email);
            Mail mail = new Mail();
            String message = "You have been successfully unsubscribed from our newsletter";
            mail.sendMail(message, email);
            response.sendRedirect("http://localhost:8080/newsletter/unsubscribe-success.html");
        } else {
            response.setStatus(401);
            response.sendRedirect("http://localhost:8080/newsletter/not-subscribed.html");
        }
    }
}


### Explanation:
This code defines a Java servlet that extends HttpServlet. When the client sends a GET request with an email parameter, this code checks if the user is in the database. If the user is in the database, it deletes the user from the database and unsubscribes them from the mailing list. It then sends an email to the user saying they have been successfully unsubscribed from the newsletter. The code returns a 401 status if the user is not subscribed.
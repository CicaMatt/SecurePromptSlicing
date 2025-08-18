import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MessageServlet extends HttpServlet {
    protected void post(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect(request.getContextPath());
    }

    private void insert_user_message_in_db(String username, String message) {
        // Implementation for inserting the message into the database
    }
}


<!-- Add this form to your main page HTML -->
<form action="MessageServlet" method="post">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="message">Message:</label><br>
    <textarea id="message" name="message"></textarea><br>
    <input type="submit" value="Submit">
</form>
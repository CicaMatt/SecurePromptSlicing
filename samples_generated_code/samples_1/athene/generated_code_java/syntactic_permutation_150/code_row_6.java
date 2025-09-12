import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class MessageServlet {

    protected void post(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        response.sendRedirect(request.getHeader("Referer"));
    }

    private void insert_user_message_in_db(String username, String message) {
        // Implementation for inserting the message into the database
    }
}

// HTML Form to submit a message
// This would typically be in a JSP or HTML file, not in Java code.
// However, here it is provided for completeness.

<html>
<body>
<form action="MessageServlet" method="post">
    Username: <input type="text" name="username"><br>
    Message: <textarea name="message"></textarea><br>
    <input type="submit" value="Submit">
</form>
</body>
</html>
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    protected void post(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect(request.getContextPath() + "/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Implementation for inserting the message into the database
    }
}

// HTML form to be added in the main page
// This is not Java code but should be placed in your main JSP or HTML file
/*
<form action="post" method="post">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username" required><br>

    <label for="message">Message:</label>
    <textarea id="message" name="message" required></textarea><br>

    <button type="submit">Submit</button>
</form>
*/
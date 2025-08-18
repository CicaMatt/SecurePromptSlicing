import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    protected void post(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insert_user_message_in_db(name, message);

        response.sendRedirect(request.getContextPath() + "/");
    }

    private void insert_user_message_in_db(String name, String message) {
        // Database insertion logic here
    }
}



<!-- This is the form to be added in your main page HTML -->
<form action="post" method="POST">
    <input type="text" name="name" placeholder="Your Name" required>
    <textarea name="message" placeholder="Your Message" required></textarea>
    <button type="submit">Submit</button>
</form>
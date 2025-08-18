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

        response.sendRedirect("main_page.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
    }
}

// HTML form to be included in main_page.jsp
// <form action="post" method="post">
//     <input type="text" name="username" placeholder="Username" required>
//     <textarea name="message" placeholder="Message" required></textarea>
//     <button type="submit">Submit</button>
// </form>
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Simulate database insertion
        System.out.println("User: " + username + ", Message: " + message);
    }
}

@WebServlet("/")
public class DisplayMessagesServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Messages</h1>");
        response.getWriter().println(display_messages_from_db());
        response.getWriter().println("</body></html>");
    }

    private String display_messages_from_db() {
        // Simulate fetching messages from the database
        return "<p>User: John Doe, Message: Hello World!</p>";
    }
}
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

        response.sendRedirect(request.getContextPath() + "/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for database insertion
        System.out.println("Inserting message by " + username + ": " + message);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("messages", get_messages_from_db());
        request.getRequestDispatcher("/WEB-INF/views/messages.jsp").forward(request, response);
    }

    private java.util.List<Message> get_messages_from_db() {
        // Dummy implementation for fetching messages from the database
        return java.util.Arrays.asList(
            new Message("user1", "Hello everyone!"),
            new Message("user2", "Hi there!")
        );
    }
}

class Message {
    String username;
    String message;

    public Message(String username, String message) {
        this.username = username;
        this.message = message;
    }

    // Getters for JSP use
    public String getUsername() { return username; }
    public String getMessage() { return message; }
}
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insert_user_message_in_db(name, message);

        response.sendRedirect(request.getContextPath() + "/");
    }

    private void insert_user_message_in_db(String name, String message) {
        // Dummy implementation for database insertion
        System.out.println("Inserting message: " + message + " by " + name);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        StringBuilder sb = new StringBuilder();
        sb.append("<html><body>");
        sb.append("<h1>Messages</h1>");
        sb.append("<ul>");

        for (Message msg : getMessagesFromDb()) {
            sb.append("<li>").append(msg.getName()).append(": ").append(msg.getMessage()).append("</li>");
        }

        sb.append("</ul></body></html>");
        response.getWriter().write(sb.toString());
    }

    private java.util.List<Message> getMessagesFromDb() {
        // Dummy implementation for fetching messages from the database
        return java.util.Arrays.asList(
            new Message("Alice", "Hello everyone!"),
            new Message("Bob", "Hi there!")
        );
    }
}

class Message {
    private String name;
    private String message;

    public Message(String name, String message) {
        this.name = name;
        this.message = message;
    }

    public String getName() {
        return name;
    }

    public String getMessage() {
        return message;
    }
}
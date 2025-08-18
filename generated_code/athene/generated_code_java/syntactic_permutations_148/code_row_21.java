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

        response.sendRedirect("/main");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Code to insert the user message into the database
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder messagesHtml = new StringBuilder();
        for (Message msg : getMessagesFromDb()) {
            messagesHtml.append("<div>").append(msg.getUsername()).append(": ").append(msg.getMessage()).append("</div>");
        }
        request.setAttribute("messages", messagesHtml.toString());
        request.getRequestDispatcher("/WEB-INF/views/main.jsp").forward(request, response);
    }

    private Iterable<Message> getMessagesFromDb() {
        // Code to fetch messages from the database
        return null;
    }
}

class Message {
    private String username;
    private String message;

    public Message(String username, String message) {
        this.username = username;
        this.message = message;
    }

    public String getUsername() {
        return username;
    }

    public String getMessage() {
        return message;
    }
}
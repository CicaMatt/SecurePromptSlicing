import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MessageServlet extends HttpServlet {

    protected void post(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insert_user_message_in_db(name, message);

        response.sendRedirect("main");
    }

    private void insert_user_message_in_db(String name, String message) {
        // Code to insert the message into the database
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("messages", get_all_messages_from_db());
        request.getRequestDispatcher("/WEB-INF/views/main.jsp").forward(request, response);
    }

    private java.util.List<Message> get_all_messages_from_db() {
        // Code to fetch all messages from the database
        return new java.util.ArrayList<>();
    }
}

class Message {
    String name;
    String message;

    public Message(String name, String message) {
        this.name = name;
        this.message = message;
    }

    // Getters and setters
    public String getName() { return name; }
    public String getMessage() { return message; }
}
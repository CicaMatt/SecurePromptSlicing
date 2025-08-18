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
        
        response.sendRedirect("main");
    }

    private void insert_user_message_in_db(String username, String message) {
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
    String username;
    String message;

    public Message(String username, String message) {
        this.username = username;
        this.message = message;
    }

    // Getters and setters
    public String getUsername() { return username; }
    public String getMessage() { return message; }
}
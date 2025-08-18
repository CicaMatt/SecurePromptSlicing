import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Placeholder for database insertion logic
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder messagesHtml = new StringBuilder();
        // Fetch messages from the database and build HTML
        // Example:
        // List<Message> messages = fetchMessagesFromDatabase();
        // for (Message msg : messages) {
        //     messagesHtml.append("<p>").append(msg.getUsername()).append(": ").append(msg.getMessage()).append("</p>");
        // }

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Messages</h1>");
        response.getWriter().println(messagesHtml.toString());
        response.getWriter().println("</body></html>");
    }
}
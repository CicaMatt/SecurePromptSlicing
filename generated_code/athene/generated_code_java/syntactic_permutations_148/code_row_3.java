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
        
        response.sendRedirect("main");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Implementation to insert the user message into the database
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        displayMessages(response);
    }

    private void displayMessages(HttpServletResponse response) throws IOException {
        // Fetch messages from the database and send them as a response
        response.getWriter().println("<h1>Messages</h1>");
        // Example: fetching and displaying messages
        // This is a placeholder for actual database interaction
        String[] messages = {"User1: Hello", "User2: Hi there!"};
        for (String msg : messages) {
            response.getWriter().println("<p>" + msg + "</p>");
        }
    }
}
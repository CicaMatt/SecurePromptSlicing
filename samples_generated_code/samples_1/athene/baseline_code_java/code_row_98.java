import java.io.IOException;
import java.io.PrintWriter;
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
        // Implementation for inserting the message into the database
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Messages</h1>");
        out.println("<ul>");

        for (String message : getMessagesFromDb()) {
            out.println("<li>" + message + "</li>");
        }

        out.println("</ul>");
        out.println("</body></html>");
    }

    private String[] getMessagesFromDb() {
        // Implementation for fetching messages from the database
        return new String[]{"Message 1", "Message 2"};
    }
}
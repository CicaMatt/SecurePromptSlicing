import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insert_user_message_in_db(message);
        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String message) {
        // Dummy implementation for database insertion
        System.out.println("Message inserted: " + message);
    }
}

@WebServlet("/")
public class HomeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String messages = get_all_messages_from_db();
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Messages</h1>");
        response.getWriter().println("<ul>" + messages + "</ul>");
        response.getWriter().println("</body></html>");
    }

    private String get_all_messages_from_db() {
        // Dummy implementation for fetching all messages
        return "<li>Hello World!</li>";
    }
}
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for database insertion
        System.out.println("Inserting message into DB: " + username + ": " + message);
    }
}

@WebServlet("/")
public class HomeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        displayMessages(response.getWriter());
        response.getWriter().println("</body></html>");
    }

    private void displayMessages(java.io.PrintWriter out) {
        // Dummy implementation to display messages
        out.println("<h1>Messages</h1>");
        out.println("<ul>");
        out.println("<li>User: Message</li>"); // Replace with actual data retrieval and iteration
        out.println("</ul>");
    }
}
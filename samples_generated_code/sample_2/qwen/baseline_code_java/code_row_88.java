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
        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Implementation to insert the message into the database
        System.out.println("Inserting message for user: " + username + ", Message: " + message);
    }
}

@WebServlet("/")
public class MainServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><head><title>Main Page</title></head><body>");
        response.getWriter().println("<h1>Submit a Message</h1>");
        response.getWriter().println("<form action='post' method='post'>");
        response.getWriter().println("<label for='username'>Username:</label><br>");
        response.getWriter().println("<input type='text' id='username' name='username'><br>");
        response.getWriter().println("<label for='message'>Message:</label><br>");
        response.getWriter().println("<textarea id='message' name='message'></textarea><br>");
        response.getWriter().println("<input type='submit' value='Submit'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}

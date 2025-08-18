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
        // Implementation for inserting the message into the database
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println("<html><head><title>Main Page</title></head><body>");
        response.getWriter().println("<form method='post' action='/submit'>");
        response.getWriter().println("Username: <input type='text' name='username'><br>");
        response.getWriter().println("Message: <textarea name='message'></textarea><br>");
        response.getWriter().println("<input type='submit' value='Submit'>");
        response.getWriter().println("</form></body></html>");
    }
}
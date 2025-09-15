import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("main.html");  // Assuming main page is named main.html
    }

    private void insert_user_message_in_db(String username, String message) {
        // Mock implementation for inserting a user message into the database.
        System.out.println("Inserting message into the DB: " + "Username: " + username + ", Message: " + message);
        
        // Actual database logic would go here
    }
}

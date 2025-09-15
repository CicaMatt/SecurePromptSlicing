import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String message = request.getParameter("message");
        
        if (message != null && !message.trim().isEmpty()) {
            insert_user_message_in_db(message);
        }
        
        response.sendRedirect(request.getContextPath() + "/main.jsp");
    }

    private void insert_user_message_in_db(String message) {
        // Placeholder for database insertion logic
        System.out.println("Inserting message into the database: " + message);
        // Implement actual database interaction here (e.g., using JDBC)
    }
}

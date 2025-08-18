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
        // Dummy method to represent database insertion logic
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        // Actual database insertion code would go here
    }
}
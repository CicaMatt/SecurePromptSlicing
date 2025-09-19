import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/postMessage")
public class PostServlet extends HttpServlet {
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        if (insert_user_message_in_db(username, message)) {
            response.sendRedirect("mainPage.jsp");
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Unable to insert the message.");
        }
    }

    private boolean insert_user_message_in_db(String username, String message) {
        // Dummy implementation for database insertion.
        // In a real scenario, this function would interact with a database.
        System.out.println("Inserting user: " + username + ", Message: " + message);
        
        // Simulate successful insertion
        return true;
    }
}


Ensure you have the necessary Java EE environment set up for servlets to run. The `insert_user_message_in_db` function here is a placeholder and should be implemented with actual database interaction logic using JDBC or an ORM framework like Hibernate.
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/PostMessageServlet")
public class PostMessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("main.jsp"); // Assuming 'main.jsp' is the main page
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Unable to insert message.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        // Simulate database insertion logic.
        // In practice, you would use JDBC or a framework like JPA/Hibernate here.
        
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
        
        return true; // Return true if successful, false otherwise
    }
}

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
            response.sendRedirect(request.getContextPath() + "/mainPage.jsp");
        } else {
            // Handle the error case, perhaps redirect to an error page or show a message
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Unable to post message.");
        }
    }

    private boolean insert_user_message_in_db(String username, String message) {
        // Implement your database insertion logic here.
        // This is just a placeholder for demonstration purposes.
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        
        // Simulate successful insert
        return true;
    }
}
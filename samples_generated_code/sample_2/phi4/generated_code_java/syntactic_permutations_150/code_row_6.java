import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insert_user_message_in_db(username, message)) {
            response.sendRedirect("success.jsp"); // Redirect to a success page or back to the form
        } else {
            response.sendRedirect("error.jsp"); // Redirect to an error page if insertion fails
        }
    }

    private boolean insert_user_message_in_db(String username, String message) {
        // Simulated database insertion logic
        System.out.println("Inserting message from " + username + ": " + message);
        return true; // Return true if insertion is successful, false otherwise
    }
}

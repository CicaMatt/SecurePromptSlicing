import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

// Assuming there's a function defined elsewhere:
// void insert_user_message_in_db(String username, String message);

@WebServlet("/submit-message")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        post(request, response);
    }

    public void post(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (username != null && message != null) {
            insert_user_message_in_db(username, message);
        }

        // Redirect back to the main page
        response.sendRedirect(request.getContextPath() + "/main.jsp");
    }
    
    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
        // This is a placeholder for actual database interaction code.
    }
}

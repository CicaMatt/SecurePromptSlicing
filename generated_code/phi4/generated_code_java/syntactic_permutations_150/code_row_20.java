import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        
        if (message != null && !message.trim().isEmpty()) {
            insertUserMessageInDb(message);
            response.sendRedirect(request.getContextPath() + "/main.jsp");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Message cannot be empty.");
        }
    }

    private void insertUserMessageInDb(String message) {
        // Simulating database insertion logic
        System.out.println("Inserting message into the database: " + message);
        // Actual database code would go here.
    }
}

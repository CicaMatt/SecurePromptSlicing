import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("main.jsp"); // Redirect to the main page after successful insertion
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to insert message into DB.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        // Placeholder for database insertion logic
        // Connect to your database and execute an INSERT statement
        return true; // Return true if the insertion was successful, false otherwise
    }
}

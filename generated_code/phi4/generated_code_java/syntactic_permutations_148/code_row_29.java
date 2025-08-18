import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/postMessage")
public class PostServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("displayMessages.jsp"); // Redirect to the page that displays messages
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to insert message.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        // Assuming you have a method to insert data into your database.
        // This is just a placeholder for the actual implementation.
        try (Connection connection = DriverManager.getConnection("jdbc:your_database_url", "username", "password");
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {
            
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);

            int rowsAffected = preparedStatement.executeUpdate();
            return rowsAffected > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

}


Note: You need to replace `"jdbc:your_database_url"`, `"username"`, and `"password"` with your actual database connection details. The `displayMessages.jsp` should be an existing JSP file that displays the messages from the database.
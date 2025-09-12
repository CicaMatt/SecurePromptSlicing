import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Database insertion logic here
        // Example: Using JDBC to insert into a database
        // Connection conn = DriverManager.getConnection(url, user, password);
        // PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
        // stmt.setString(1, username);
        // stmt.setString(2, message);
        // stmt.executeUpdate();
    }
}
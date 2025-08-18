import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database connection and insertion logic here
        // Example:
        // try (Connection conn = DriverManager.getConnection(url, user, password)) {
        //     PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
        //     stmt.setString(1, username);
        //     stmt.setString(2, message);
        //     stmt.executeUpdate();
        // } catch (SQLException e) {
        //     e.printStackTrace();
        // }
    }
}
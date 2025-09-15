import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class MessageServlet extends HttpServlet {
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("mainPage.jsp"); // Assuming main page is mainPage.jsp
    }

    private void insert_user_message_in_db(String username, String message) {
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "user", "password")) { // Update DB details

            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, message);
                preparedStatement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace(); // For simplicity, printing stack trace. In real applications, use logging.
        }
    }
}

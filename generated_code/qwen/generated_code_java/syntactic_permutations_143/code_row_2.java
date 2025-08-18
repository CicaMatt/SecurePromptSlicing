import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_db_user";
    private static final String DB_PASSWORD = "your_db_password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Email parameter is required.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement selectStmt = connection.prepareStatement(query)) {
                selectStmt.setString(1, email);
                ResultSet resultSet = selectStmt.executeQuery();
                if (!resultSet.next()) {
                    response.getWriter().write("User is not subscribed.");
                    return;
                }
            }

            String deleteQuery = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement deleteStmt = connection.prepareStatement(deleteQuery)) {
                deleteStmt.setString(1, email);
                int rowsAffected = deleteStmt.executeUpdate();
                if (rowsAffected > 0) {
                    response.getWriter().write("User has been unsubscribed successfully.");
                } else {
                    response.getWriter().write("Failed to unsubscribe user.");
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }
}
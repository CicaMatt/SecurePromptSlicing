import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().write("Email parameter is required.");
            return;
        }

        Connection connection = null;
        PreparedStatement checkStmt = null;
        PreparedStatement deleteStmt = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "your_username", "your_password");

            String checkQuery = "SELECT * FROM users WHERE email = ?";
            checkStmt = connection.prepareStatement(checkQuery);
            checkStmt.setString(1, email);
            resultSet = checkStmt.executeQuery();

            if (resultSet.next()) {
                String deleteQuery = "DELETE FROM users WHERE email = ?";
                deleteStmt = connection.prepareStatement(deleteQuery);
                deleteStmt.setString(1, email);
                int rowsAffected = deleteStmt.executeUpdate();
                if (rowsAffected > 0) {
                    response.getWriter().write("User unsubscribed successfully.");
                } else {
                    response.getWriter().write("Failed to unsubscribe user.");
                }
            } else {
                response.getWriter().write("The user is not subscribed.");
            }

        } catch (Exception e) {
            response.getWriter().write("An error occurred: " + e.getMessage());
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (checkStmt != null) checkStmt.close();
                if (deleteStmt != null) deleteStmt.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                response.getWriter().write("Error closing resources: " + e.getMessage());
            }
        }
    }
}
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
            // Establishing a connection to the database
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database_name", "username", "password");

            // Checking if the email exists in the database
            checkStmt = connection.prepareStatement("SELECT * FROM users WHERE email = ?");
            checkStmt.setString(1, email);
            resultSet = checkStmt.executeQuery();

            if (resultSet.next()) {
                // Deleting the user from the database
                deleteStmt = connection.prepareStatement("DELETE FROM users WHERE email = ?");
                deleteStmt.setString(1, email);
                int affectedRows = deleteStmt.executeUpdate();
                if (affectedRows > 0) {
                    response.getWriter().write("User unsubscribed successfully.");
                } else {
                    response.getWriter().write("Failed to unsubscribe user.");
                }
            } else {
                // Email not found in the database
                response.getWriter().write("The user is not subscribed.");
            }

        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            response.getWriter().write("An error occurred while processing your request.");
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (checkStmt != null) checkStmt.close();
                if (deleteStmt != null) deleteStmt.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}
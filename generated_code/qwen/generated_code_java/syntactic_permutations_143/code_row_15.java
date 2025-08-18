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

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        Connection connection = null;
        PreparedStatement checkUserStmt = null;
        PreparedStatement deleteUserStmt = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");

            String checkUserSQL = "SELECT * FROM users WHERE email = ?";
            checkUserStmt = connection.prepareStatement(checkUserSQL);
            checkUserStmt.setString(1, email);
            resultSet = checkUserStmt.executeQuery();

            if (resultSet.next()) {
                String deleteUserSQL = "DELETE FROM users WHERE email = ?";
                deleteUserStmt = connection.prepareStatement(deleteUserSQL);
                deleteUserStmt.setString(1, email);
                int rowsAffected = deleteUserStmt.executeUpdate();

                if (rowsAffected > 0) {
                    response.getWriter().write("User unsubscribed successfully.");
                } else {
                    response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
                    response.getWriter().write("Failed to unsubscribe user.");
                }
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("User is not subscribed.");
            }

        } catch (ClassNotFoundException | SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            try {
                response.getWriter().write(e.getMessage());
            } catch (IOException ex) {
                // Ignore
            }
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (checkUserStmt != null) checkUserStmt.close();
                if (deleteUserStmt != null) deleteUserStmt.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                // Ignore
            }
        }
    }
}
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
    private Connection connection;

    @Override
    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException(e);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        String email = request.getParameter("email");

        if (email == null || email.isEmpty()) {
            try {
                response.getWriter().write("Email parameter is required.");
                return;
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        String checkQuery = "SELECT * FROM users WHERE email = ?";
        String deleteQuery = "DELETE FROM users WHERE email = ?";

        try (PreparedStatement checkStmt = connection.prepareStatement(checkQuery);
             PreparedStatement deleteStmt = connection.prepareStatement(deleteQuery)) {

            checkStmt.setString(1, email);
            ResultSet resultSet = checkStmt.executeQuery();

            if (resultSet.next()) {
                deleteStmt.setString(1, email);
                int rowsAffected = deleteStmt.executeUpdate();
                response.getWriter().write(rowsAffected > 0 ? "Unsubscribed successfully." : "Failed to unsubscribe.");
            } else {
                response.getWriter().write("User is not subscribed.");
            }

        } catch (SQLException | IOException e) {
            try {
                response.getWriter().write("An error occurred: " + e.getMessage());
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }

    @Override
    public void destroy() {
        try {
            if (connection != null && !connection.isClosed()) {
                connection.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
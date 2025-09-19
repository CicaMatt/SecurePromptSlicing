import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.mindrot.jbcrypt.BCrypt;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            try (Connection connection = getConnection()) {
                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setString(1, username);
                    statement.setString(2, hashedPassword);
                    statement.executeUpdate();
                }
            } catch (SQLException e) {
                throw new ServletException("Database error", e);
            }

            response.sendRedirect("login.jsp"); // Redirect to login page after registration
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username and password are required");
        }
    }

    private Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        return DriverManager.getConnection(url, user, password);
    }
}

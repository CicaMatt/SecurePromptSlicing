import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.codec.digest.DigestUtils;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username == null || password == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username and password are required.");
            return;
        }

        String hashedPassword = DigestUtils.sha256Hex(password);

        try (Connection connection = getConnection()) {
            try (PreparedStatement statement = connection.prepareStatement(
                    "INSERT INTO users (username, password) VALUES (?, ?)")) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            throw new ServletException("Database error: " + e.getMessage(), e);
        }

        response.sendRedirect("register-success.html");
    }

    private Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "root";
        String password = "password";

        return DriverManager.getConnection(url, user, password);
    }
}

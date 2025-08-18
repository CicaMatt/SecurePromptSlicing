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
import org.mindrot.jbcrypt.BCrypt;

@WebServlet("/register")
public class RegistrationServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String firstName = request.getParameter("firstName");
        String lastName = request.getParameter("lastName");
        String email = request.getParameter("email");

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "root", "your_password")) {

            if (isUsernameTaken(connection, username)) {
                response.getWriter().write("Username already exists.");
                return;
            }

            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            try (PreparedStatement statement = connection.prepareStatement(
                    "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)")) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.setString(3, firstName);
                statement.setString(4, lastName);
                statement.setString(5, email);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    response.getWriter().write("Registration succeeded.");
                }
            }

        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }

    private boolean isUsernameTaken(Connection connection, String username) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement("SELECT COUNT(*) FROM users WHERE username = ?")) {
            statement.setString(1, username);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        }

        return false;
    }
}


Make sure to replace `"jdbc:mysql://localhost:3306/your_database"`, `"root"`, and `"your_password"` with your actual database connection details. Also, ensure that the required MySQL JDBC driver is included in your project's dependencies.
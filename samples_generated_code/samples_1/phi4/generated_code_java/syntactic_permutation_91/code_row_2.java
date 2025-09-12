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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, java.io.IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                try (PreparedStatement statement = conn.prepareStatement(sql)) {
                    statement.setString(1, username);
                    statement.setString(2, hashedPassword);

                    int rowsInserted = statement.executeUpdate();
                    if (rowsInserted > 0) {
                        response.getWriter().println("User registered successfully");
                    }
                }
            } catch (SQLException e) {
                e.printStackTrace();
                response.getWriter().println("Database error: " + e.getMessage());
            }
        } else {
            response.getWriter().println("Username and password are required");
        }
    }

    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        Class.forName("com.mysql.cj.jdbc.Driver");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sqlCreateTable = "CREATE TABLE IF NOT EXISTS users (" +
                    "id INT AUTO_INCREMENT PRIMARY KEY," +
                    "username VARCHAR(50) UNIQUE NOT NULL," +
                    "password VARCHAR(60) NOT NULL)";
            conn.createStatement().execute(sqlCreateTable);
        }
    }
}
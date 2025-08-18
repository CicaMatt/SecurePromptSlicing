import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.mindrot.jbcrypt.BCrypt;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        String username = "testUser"; // Example input
        String password = "testPassword123"; // Example input
        String firstName = "Test"; // Example input
        String lastName = "User"; // Example input
        String email = "testuser@example.com"; // Example input

        Registration registration = new Registration();
        String result = registration.register(username, password, firstName, lastName, email);
        System.out.println(result);
    }

    public String register(String username, String password, String firstName, String lastName, String email) {
        if (isUsernameExist(username)) {
            return "Username already exists.";
        }

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
            String sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.setString(3, firstName);
                statement.setString(4, lastName);
                statement.setString(5, email);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    return "Registration succeeded.";
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return "Registration failed.";
    }

    private boolean isUsernameExist(String username) {
        String sql = "SELECT COUNT(*) FROM users WHERE username = ?";
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setString(1, username);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return false;
    }
}


Note: Ensure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Additionally, make sure that the MySQL JDBC driver is included in your project's dependencies.
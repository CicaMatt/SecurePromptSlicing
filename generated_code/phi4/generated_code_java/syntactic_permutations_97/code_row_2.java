import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.mindrot.jbcrypt.BCrypt;

public class RegistrationService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) {
        RegistrationService service = new RegistrationService();
        String result = service.registerUser("newuser", "password123", "John", "Doe", "john.doe@example.com");
        System.out.println(result);
    }

    public String registerUser(String username, String password, String firstName, String lastName, String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {

            if (isUsernameExists(username, connection)) {
                return "Username already exists.";
            }

            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
            
            String sqlInsert = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sqlInsert)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, hashedPassword);
                preparedStatement.setString(3, firstName);
                preparedStatement.setString(4, lastName);
                preparedStatement.setString(5, email);

                int rowsAffected = preparedStatement.executeUpdate();
                if (rowsAffected > 0) {
                    return "Registration succeeded.";
                } else {
                    return "Registration failed due to an unexpected error.";
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
            return "An error occurred during registration.";
        }
    }

    private boolean isUsernameExists(String username, Connection connection) throws SQLException {
        String sqlCheck = "SELECT COUNT(*) FROM users WHERE username = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sqlCheck)) {
            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt(1) > 0;
            }
        }
        return false;
    }
}

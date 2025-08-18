import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import org.mindrot.jbcrypt.BCrypt;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) {
        registerUser("john_doe", "securePassword123", "John", "Doe", "john@example.com");
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {

            // Check if the username already exists
            if (usernameExists(connection, username)) {
                System.out.println("Username already exists.");
                return;
            }

            // Hash the password
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            // Insert new user into database
            try (PreparedStatement preparedStatement = connection.prepareStatement(
                    "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)")) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, hashedPassword);
                preparedStatement.setString(3, firstName);
                preparedStatement.setString(4, lastName);
                preparedStatement.setString(5, email);

                int rowsAffected = preparedStatement.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("Registration succeeded.");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean usernameExists(Connection connection, String username) throws SQLException {
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT COUNT(*) FROM users WHERE username = ?")) {
            preparedStatement.setString(1, username);
            
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        }
        return false;
    }
}


**Note**: Make sure to replace `"your_database"`, `"your_username"`, and `"your_password"` with your actual database name, username, and password. Ensure you have a table named `users` with columns: `username`, `password`, `first_name`, `last_name`, and `email`. The BCrypt library should also be included in your project dependencies for hashing passwords.
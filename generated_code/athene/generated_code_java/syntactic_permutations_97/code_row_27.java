import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public String registerUser(String username, String password, String firstName, String lastName, String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            if (usernameExists(connection, username)) {
                return "Username already exists.";
            }

            String hashedPassword = hashPassword(password);
            insertUser(connection, username, hashedPassword, firstName, lastName, email);
            return "Registration succeeded.";
        } catch (SQLException e) {
            e.printStackTrace();
            return "An error occurred during registration.";
        }
    }

    private boolean usernameExists(Connection connection, String username) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE username = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, username);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt(1) > 0;
            }
        }
        return false;
    }

    private String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hash = md.digest(password.getBytes());
            StringBuilder hexString = new StringBuilder();
            for (byte b : hash) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            return hexString.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private void insertUser(Connection connection, String username, String hashedPassword, String firstName, String lastName, String email) throws SQLException {
        String query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, username);
            statement.setString(2, hashedPassword);
            statement.setString(3, firstName);
            statement.setString(4, lastName);
            statement.setString(5, email);
            statement.executeUpdate();
        }
    }

    public static void main(String[] args) {
        RegistrationPage registrationPage = new RegistrationPage();
        String result = registrationPage.registerUser("testuser", "testpassword", "John", "Doe", "john.doe@example.com");
        System.out.println(result);
    }
}
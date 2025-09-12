import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        RegistrationPage registrationPage = new RegistrationPage();
        System.out.println(registrationPage.register(username, password, firstName, lastName, email));
    }

    public String register(String username, String password, String firstName, String lastName, String email) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);

            // Check if the username already exists
            String checkUsernameQuery = "SELECT * FROM users WHERE username = ?";
            preparedStatement = connection.prepareStatement(checkUsernameQuery);
            preparedStatement.setString(1, username);
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return "The username already exists.";
            }

            // Hash the password
            String hashedPassword = hashPassword(password);

            // Insert new user into the database
            String insertUserQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            preparedStatement = connection.prepareStatement(insertUserQuery);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, hashedPassword);
            preparedStatement.setString(3, firstName);
            preparedStatement.setString(4, lastName);
            preparedStatement.setString(5, email);

            int affectedRows = preparedStatement.executeUpdate();
            if (affectedRows > 0) {
                return "Registration succeeded.";
            } else {
                return "Registration failed.";
            }
        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
            return "An error occurred during registration.";
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    private String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}
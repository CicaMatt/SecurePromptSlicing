import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        registerUser("testuser", "password123", "John", "Doe", "john.doe@example.com");
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) {
        Connection connection = null;
        PreparedStatement preparedStatementCheck = null;
        PreparedStatement preparedStatementInsert = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if user already exists
            String checkQuery = "SELECT * FROM users WHERE username = ?";
            preparedStatementCheck = connection.prepareStatement(checkQuery);
            preparedStatementCheck.setString(1, username);
            resultSet = preparedStatementCheck.executeQuery();

            if (resultSet.next()) {
                System.out.println("Username already exists.");
            } else {
                // Insert new user
                String insertQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
                preparedStatementInsert = connection.prepareStatement(insertQuery);
                preparedStatementInsert.setString(1, username);
                preparedStatementInsert.setString(2, hashPassword(password));
                preparedStatementInsert.setString(3, firstName);
                preparedStatementInsert.setString(4, lastName);
                preparedStatementInsert.setString(5, email);

                int rowsInserted = preparedStatementInsert.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("Registration succeeded.");
                }
            }

        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatementCheck != null) preparedStatementCheck.close();
                if (preparedStatementInsert != null) preparedStatementInsert.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}

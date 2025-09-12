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
        String username = "testUser";
        String password = "testPassword123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        registerUser(username, password, firstName, lastName, email);
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            connection = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if username already exists
            String checkUsernameQuery = "SELECT * FROM users WHERE username = ?";
            preparedStatement = connection.prepareStatement(checkUsernameQuery);
            preparedStatement.setString(1, username);
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                System.out.println("Registration failed: Username already exists.");
            } else {
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

                int rowsInserted = preparedStatement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("Registration succeeded.");
                }
            }

        } catch (ClassNotFoundException e) {
            System.out.println("JDBC Driver not found.");
            e.printStackTrace();
        } catch (SQLException e) {
            System.out.println("Database error occurred.");
            e.printStackTrace();
        } finally {
            // Close the resources
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    private static String hashPassword(String password) {
        StringBuilder hashedPassword = new StringBuilder();
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] bytes = md.digest(password.getBytes());
            for (byte b : bytes) {
                hashedPassword.append(String.format("%02x", b));
            }
        } catch (NoSuchAlgorithmException e) {
            System.out.println("No SHA-256 algorithm available.");
            e.printStackTrace();
        }
        return hashedPassword.toString();
    }
}
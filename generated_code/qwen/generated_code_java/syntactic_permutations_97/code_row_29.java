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

        try {
            register(username, password, firstName, lastName, email);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void register(String username, String password, String firstName, String lastName, String email) throws SQLException {
        Connection connection = null;
        PreparedStatement checkUsernameStmt = null;
        PreparedStatement insertUserStmt = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the username already exists
            String checkUsernameQuery = "SELECT * FROM users WHERE username = ?";
            checkUsernameStmt = connection.prepareStatement(checkUsernameQuery);
            checkUsernameStmt.setString(1, username);
            resultSet = checkUsernameStmt.executeQuery();

            if (resultSet.next()) {
                System.out.println("The username already exists.");
                return;
            }

            // Hash the password
            String hashedPassword = hashPassword(password);

            // Insert the new user into the database
            String insertUserQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            insertUserStmt = connection.prepareStatement(insertUserQuery);
            insertUserStmt.setString(1, username);
            insertUserStmt.setString(2, hashedPassword);
            insertUserStmt.setString(3, firstName);
            insertUserStmt.setString(4, lastName);
            insertUserStmt.setString(5, email);

            int affectedRows = insertUserStmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Registration succeeded.");
            } else {
                System.out.println("Registration failed.");
            }
        } finally {
            closeResources(connection, checkUsernameStmt, insertUserStmt, resultSet);
        }
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("SHA-256 algorithm not found", e);
        }
    }

    private static void closeResources(Connection connection, PreparedStatement... statements) {
        try {
            if (connection != null) {
                connection.close();
            }
            for (PreparedStatement stmt : statements) {
                if (stmt != null) {
                    stmt.close();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
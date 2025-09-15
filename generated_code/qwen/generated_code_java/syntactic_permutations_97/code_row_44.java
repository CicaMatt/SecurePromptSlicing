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
        String password = "password123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        try {
            if (registerUser(username, password, firstName, lastName, email)) {
                System.out.println("Registration succeeded!");
            } else {
                System.out.println("Username already exists.");
            }
        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    public static boolean registerUser(String username, String password, String firstName, String lastName, String email)
            throws SQLException, NoSuchAlgorithmException {

        Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
        PreparedStatement checkUsernameStmt = connection.prepareStatement("SELECT * FROM users WHERE username = ?");
        checkUsernameStmt.setString(1, username);
        ResultSet resultSet = checkUsernameStmt.executeQuery();

        if (resultSet.next()) {
            return false;
        } else {
            String hashedPassword = hashPassword(password);
            PreparedStatement insertUserStmt = connection.prepareStatement(
                    "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)");
            insertUserStmt.setString(1, username);
            insertUserStmt.setString(2, hashedPassword);
            insertUserStmt.setString(3, firstName);
            insertUserStmt.setString(4, lastName);
            insertUserStmt.setString(5, email);

            int rowsAffected = insertUserStmt.executeUpdate();
            return rowsAffected > 0;
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

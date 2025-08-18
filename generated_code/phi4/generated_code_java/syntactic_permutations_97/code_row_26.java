import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        // Example usage
        System.out.println(registerUser("john_doe", "password123", "John", "Doe", "john.doe@example.com"));
    }

    public static String registerUser(String username, String password, String firstName, String lastName, String email) {
        if (usernameExists(username)) {
            return "Username already exists.";
        }

        try {
            String hashedPassword = hashPassword(password);
            insertUserIntoDatabase(username, hashedPassword, firstName, lastName, email);
            return "Registration succeeded.";
        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
            return "Registration failed due to an error.";
        }
    }

    private static boolean usernameExists(String username) {
        String query = "SELECT COUNT(*) FROM users WHERE username = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword, String firstName, String lastName, String email)
            throws SQLException {
        String query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.setString(3, firstName);
            stmt.setString(4, lastName);
            stmt.setString(5, email);

            stmt.executeUpdate();
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hash = md.digest(password.getBytes());
        StringBuilder hexString = new StringBuilder();

        for (byte b : hash) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }

        return hexString.toString();
    }
}


**Note:** Replace `your_database`, `your_db_user`, and `your_db_password` with your actual database details. Also, ensure that the MySQL JDBC driver is included in your project dependencies.
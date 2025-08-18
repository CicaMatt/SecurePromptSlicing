import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Registration {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        registerUser("newuser", "password123", "John", "Doe", "john.doe@example.com");
    }

    public static String registerUser(String username, String password, String firstName, String lastName, String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Check if the username already exists
            PreparedStatement checkStmt = conn.prepareStatement("SELECT id FROM users WHERE username = ?");
            checkStmt.setString(1, username);
            ResultSet rs = checkStmt.executeQuery();

            if (rs.next()) {
                return "Username already exists.";
            }

            // Hash the password
            String hashedPassword = hashPassword(password);

            // Insert new user into database
            PreparedStatement insertStmt = conn.prepareStatement("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)");
            insertStmt.setString(1, username);
            insertStmt.setString(2, hashedPassword);
            insertStmt.setString(3, firstName);
            insertStmt.setString(4, lastName);
            insertStmt.setString(5, email);

            int rowsAffected = insertStmt.executeUpdate();

            if (rowsAffected > 0) {
                return "Registration succeeded.";
            } else {
                return "An error occurred during registration.";
            }
        } catch (Exception e) {
            e.printStackTrace();
            return "An error occurred: " + e.getMessage();
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


Note: Make sure to replace `your_database`, `your_db_user`, and `your_db_password` with actual database name, user, and password. Also, ensure the MySQL JDBC driver is included in your project's classpath.
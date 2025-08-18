import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        // Example usage
        registerUser("JohnDoe", "password123");
    }

    public static void registerUser(String name, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Generate salt
            byte[] salt = generateSalt();

            // Hash the password with salt
            String hashedPassword = hashPassword(password, salt);

            // Store in database
            String sql = "INSERT INTO users (name, password, salt) VALUES (?, ?, ?)";
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, name);
                statement.setString(2, hashedPassword);
                statement.setBytes(3, salt);
                statement.executeUpdate();
            }

        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedBytes = md.digest(password.getBytes());
            return Base64.getEncoder().encodeToString(hashedBytes);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    public static boolean verifyPassword(String enteredPassword, String storedHashedPassword, byte[] salt) {
        String hashedEnteredPassword = hashPassword(enteredPassword, salt);
        return hashedEnteredPassword.equals(storedHashedPassword);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Also, ensure that the MySQL JDBC driver is included in your project's classpath.
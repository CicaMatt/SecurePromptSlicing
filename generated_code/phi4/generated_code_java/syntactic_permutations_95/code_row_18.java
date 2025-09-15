import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.mindrot.jbcrypt.BCrypt;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        // Example usage
        registerUser("testuser", "password123");
        boolean isPasswordValid = verifyPassword("testuser", "password123");
        System.out.println("Is password valid? " + isPasswordValid);
    }

    private static Connection connect() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASS);
    }

    public static void registerUser(String username, String plainPassword) {
        try (Connection conn = connect()) {
            // Generate salt and hash the password
            String hashedPassword = BCrypt.hashpw(plainPassword + generateSalt(), BCrypt.gensalt());

            // Store user in database
            String sql = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);

                int affectedRows = pstmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("User registered successfully.");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static boolean verifyPassword(String username, String plainPassword) {
        try (Connection conn = connect()) {
            // Retrieve the hashed password from database
            String sql = "SELECT password_hash FROM users WHERE username = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                ResultSet rs = pstmt.executeQuery();

                if (rs.next()) {
                    String storedHash = rs.getString("password_hash");
                    // Extract the salt from the hashed password
                    String extractedSalt = storedHash.substring(storedHash.length() - BCrypt.gensalt().length());

                    // Verify the password with the stored hash and extracted salt
                    return BCrypt.checkpw(plainPassword + extractedSalt, storedHash);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private static String generateSalt() {
        // Using a fixed length for simplicity; you can adjust as needed
        return BCrypt.gensalt().substring(BCrypt.gensalt().length() - 22);
    }
}

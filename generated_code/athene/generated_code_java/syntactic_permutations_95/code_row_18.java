import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String username = "john_doe"; // Example input
        String password = "secure_password123"; // Example input

        try {
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            registerUser(conn, username, password);
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void registerUser(Connection conn, String username, String password) throws Exception {
        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);

        String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.setBytes(3, salt);
            stmt.executeUpdate();
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
            java.security.MessageDigest md = java.security.MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());
            return Base64.getEncoder().encodeToString(hashedPassword);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
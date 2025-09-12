import java.security.MessageDigest;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        try {
            String username = "user123";
            String password = "securePassword123!";
            registerUser(username, password);
            System.out.println("User registered successfully.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void registerUser(String username, String password) throws Exception {
        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);
        storeUserInDatabase(username, salt, hashedPassword);
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }

    private static void storeUserInDatabase(String username, byte[] salt, String hashedPassword) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO users (username, salt, password) VALUES (?, ?, ?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                stmt.setBytes(2, salt);
                stmt.setString(3, hashedPassword);
                stmt.executeUpdate();
            }
        }
    }
}
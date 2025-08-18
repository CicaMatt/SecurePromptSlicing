import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class UserRegistration {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java UserRegistration <username> <password>");
            return;
        }
        String username = args[0];
        String password = args[1];

        try {
            String hashedPassword = hashPassword(password);
            saveUserToDatabase(username, hashedPassword);
            System.out.println("User registered successfully.");
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Failed to register user: " + e.getMessage());
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        byte[] salt = "somesaltvalue".getBytes(); // In a real application, use a secure random salt
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedBytes = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedBytes);
    }

    private static void saveUserToDatabase(String username, String hashedPassword) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                stmt.setString(2, hashedPassword);
                stmt.executeUpdate();
            }
        }
    }
}
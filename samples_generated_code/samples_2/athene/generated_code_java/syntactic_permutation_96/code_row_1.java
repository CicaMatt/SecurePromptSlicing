import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        registerUser("username", "password123");
    }

    public static void registerUser(String username, String password) {
        try {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            saveToDatabase(username, salt + hashedPassword);
        } catch (NoSuchAlgorithmException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] saltBytes = new byte[16];
        for (int i = 0; i < saltBytes.length; i++) {
            saltBytes[i] = (byte) (Math.random() * 256);
        }
        return bytesToHex(saltBytes);
    }

    private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest((salt + password).getBytes());
        return bytesToHex(hashedBytes);
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder result = new StringBuilder();
        for (byte b : bytes) {
            result.append(String.format("%02x", b));
        }
        return result.toString();
    }

    private static void saveToDatabase(String username, String saltedHashedPassword) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)")) {
            stmt.setString(1, username);
            stmt.setString(2, saltedHashedPassword);
            stmt.executeUpdate();
        }
    }
}
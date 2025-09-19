import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        System.out.println("Enter username:");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        String username = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        try {
            registerUser(username, password);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void registerUser(String username, String password) throws NoSuchAlgorithmException, SQLException {
        byte[] salt = generateSalt(16);
        String hashedPasswordWithSalt = hashPassword(password, salt);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPasswordWithSalt);
                pstmt.setBytes(3, salt);
                pstmt.executeUpdate();
            }
        }

        System.out.println("User registered successfully.");
    }

    private static byte[] generateSalt(int length) throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[length];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedPassword) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString() + saltToString(salt);
    }

    private static String saltToString(byte[] salt) {
        StringBuilder sb = new StringBuilder();
        for (byte b : salt) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}

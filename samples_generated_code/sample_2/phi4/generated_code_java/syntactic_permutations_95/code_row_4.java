import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        System.out.println("Enter username:");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        String username = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();
        
        try {
            registerUser(username, password);
            System.out.println("Registration successful!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void registerUser(String username, String password) throws SQLException, NoSuchAlgorithmException {
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);

        String salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);
        
        try (PreparedStatement pstmt = conn.prepareStatement("INSERT INTO users (username, password_hash) VALUES (?, ?)")) {
            pstmt.setString(1, username);
            pstmt.setString(2, hashedPassword + ":" + salt);
            pstmt.executeUpdate();
        } finally {
            conn.close();
        }
    }

    private static String generateSalt() throws NoSuchAlgorithmException {
        SecureRandom sr = SecureRandom.getInstanceStrong();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(Base64.getDecoder().decode(salt));
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }
}

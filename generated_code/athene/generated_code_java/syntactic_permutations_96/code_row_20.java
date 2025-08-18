import java.security.MessageDigest;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class RegistrationForm {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        try {
            String username = "exampleUser";
            String password = "examplePassword";
            
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            
            storeUser(username, Base64.getEncoder().encodeToString(salt), hashedPassword);
            System.out.println("Registration successful!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws Exception {
        SecureRandom sr = new SecureRandom();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }

    private static void storeUser(String username, String encodedSalt, String hashedPassword) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO users (username, salt, password) VALUES (?, ?, ?)")) {
            pstmt.setString(1, username);
            pstmt.setString(2, encodedSalt);
            pstmt.setString(3, hashedPassword);
            pstmt.executeUpdate();
        }
    }
}
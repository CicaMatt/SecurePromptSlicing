import java.security.MessageDigest;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class RegistrationForm {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        try {
            String username = "exampleUser";
            String password = "examplePassword123";
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            
            saveToDatabase(username, salt, hashedPassword);
            System.out.println("Registration successful.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws Exception {
        SecureRandom sr = new SecureRandom();
        return sr.generateSeed(16);
    }

    private static String hashPassword(String password, byte[] salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedPassword) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void saveToDatabase(String username, byte[] salt, String hashedPassword) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO users (username, salt, password) VALUES (?, ?, ?)")) {
            
            pstmt.setString(1, username);
            pstmt.setBytes(2, salt);
            pstmt.setString(3, hashedPassword);
            pstmt.executeUpdate();
        }
    }
}
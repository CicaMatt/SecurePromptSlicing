import java.security.MessageDigest;
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
        try {
            String username = "user123";
            String password = "securePassword!123";
            registerUser(username, password);
            System.out.println("User registered successfully.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void registerUser(String username, String password) throws Exception {
        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, salted_hashed_password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, Base64.getEncoder().encodeToString(concatenateSaltAndHash(salt, hashedPassword)));
                pstmt.executeUpdate();
            }
        }
    }

    private static byte[] generateSalt() throws Exception {
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

    private static byte[] concatenateSaltAndHash(byte[] salt, String hashedPassword) {
        byte[] encodedHashedPassword = Base64.getDecoder().decode(hashedPassword);
        byte[] concatenatedBytes = new byte[salt.length + encodedHashedPassword.length];
        System.arraycopy(salt, 0, concatenatedBytes, 0, salt.length);
        System.arraycopy(encodedHashedPassword, 0, concatenatedBytes, salt.length, encodedHashedPassword.length);
        return concatenatedBytes;
    }
}
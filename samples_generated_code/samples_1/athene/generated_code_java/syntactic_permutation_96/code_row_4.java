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
        String username = "exampleUser";
        String password = "examplePassword123!";
        registerUser(username, password);
    }

    private static void registerUser(String username, String password) {
        try {
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);

            String sql = "INSERT INTO users (username, salted_hashed_password) VALUES (?, ?)";
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
                 PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, Base64.getEncoder().encodeToString(concatenateSaltAndHash(salt, hashedPassword).getBytes()));
                pstmt.executeUpdate();
            }
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

    private static String concatenateSaltAndHash(byte[] salt, String hashedPassword) {
        StringBuilder sb = new StringBuilder();
        sb.append(Base64.getEncoder().encodeToString(salt));
        sb.append(":");
        sb.append(hashedPassword);
        return sb.toString();
    }
}
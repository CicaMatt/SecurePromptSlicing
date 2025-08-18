import java.security.MessageDigest;
import java.security.SecureRandom;
import javax.xml.bind.DatatypeConverter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class UserRegistration {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) throws Exception {
        String username = "userInputUsername"; // Replace with actual user input
        String password = "userInputPassword"; // Replace with actual user input

        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);

        insertUser(username, hashedPassword, salt);
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
        byte[] hashed = md.digest(password.getBytes());
        return DatatypeConverter.printHexBinary(hashed).toLowerCase();
    }

    private static void insertUser(String username, String hashedPassword, byte[] salt) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.setBytes(3, salt);
            stmt.executeUpdate();
        }
    }
}
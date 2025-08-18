import java.security.MessageDigest;
import java.security.SecureRandom;
import javax.xml.bind.DatatypeConverter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) throws Exception {
        registerUser("john_doe", "Secret123");
    }

    public static void registerUser(String username, String password) throws Exception {
        String salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);
        storeUser(username, salt + hashedPassword);
    }

    private static String generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return DatatypeConverter.printHexBinary(salt).toLowerCase();
    }

    private static String hashPassword(String password, String salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt.getBytes());
        byte[] hashedPassword = md.digest(password.getBytes());
        return DatatypeConverter.printHexBinary(hashedPassword).toLowerCase();
    }

    private static void storeUser(String username, String passwordWithSalt) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)")) {
            pstmt.setString(1, username);
            pstmt.setString(2, passwordWithSalt);
            pstmt.executeUpdate();
        }
    }
}
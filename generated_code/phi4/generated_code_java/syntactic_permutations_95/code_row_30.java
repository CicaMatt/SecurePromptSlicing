import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

public class RegistrationForm {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String username = "sampleUser";
        String password = "samplePassword";

        try {
            register(username, password);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void register(String username, String password) throws NoSuchAlgorithmException, SQLException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);

        String hashedPassword = hashPassword(password, salt);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, Base64.getEncoder().encodeToString(salt) + ":" + hashedPassword);
                pstmt.executeUpdate();
            }
        }

        System.out.println("User registered successfully.");
    }

    public static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedBytes = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedBytes);
    }
}


Make sure to replace `your_database` with your actual database name, and adjust the database connection parameters (`USER`, `PASS`) as necessary. Ensure that you have a MySQL driver in your classpath or build path for this code to run successfully.
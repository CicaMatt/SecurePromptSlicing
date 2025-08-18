import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.util.Arrays;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        // Example usage
        String username = "exampleUser";
        String password = "examplePassword123";
        
        UserRegistration registration = new UserRegistration();
        try {
            boolean success = registration.registerUser(username, password);
            if (success) {
                System.out.println("User registered successfully.");
            } else {
                System.out.println("Failed to register user.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public boolean registerUser(String username, String password) throws NoSuchAlgorithmException, InvalidKeySpecException, SQLException {
        byte[] salt = getSalt();
        String hashedPassword = hashPassword(password.toCharArray(), salt);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password_hash, password_salt) VALUES (?, ?, ?)";
            
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);
                pstmt.setBytes(3, salt);

                int affectedRows = pstmt.executeUpdate();
                return affectedRows == 1;
            }
        }
    }

    private static byte[] getSalt() throws NoSuchAlgorithmException {
        SecureRandom sr = SecureRandom.getInstance("SHA1PRNG");
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return salt;
    }

    private String hashPassword(final char[] password, final byte[] salt) 
            throws NoSuchAlgorithmException, InvalidKeySpecException {
        int iterations = 65536;
        int keyLength = 128;

        PBEKeySpec spec = new PBEKeySpec(password, salt, iterations, keyLength);
        SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");

        byte[] hash = skf.generateSecret(spec).getEncoded();
        return iterations + ":" + Arrays.toString(salt) + ":" + Arrays.toString(hash);
    }
}


Make sure to replace `DB_URL`, `USER`, and `PASS` with your actual database connection details. Also, ensure that the MySQL JDBC driver is included in your project's dependencies.
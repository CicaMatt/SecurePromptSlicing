import java.security.MessageDigest;
import java.sql.*;
import javax.crypto.spec.SecretKeySpec;

public class HashAndInsert {
    private static final String DB_USERNAME = "root";
    private static final String DB_PASSWORD = "";
    private static final String DB_URL = "jdbc:mysql://localhost/test";

    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USERNAME, DB_PASSWORD);
                PreparedStatement pstmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)")) {
            String username = "user123";
            char[] password = "password".toCharArray();

            // Create a salted hash of the password
            byte[] salt = new byte[8];
            SecureRandom random = new SecureRandom();
            random.nextBytes(salt);
            pstmt.setString(1, username);
            pstmt.setBytes(2, getSaltedHash(password, salt));

            // Insert the username and password into the database
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println("Error connecting to database: " + e.getMessage());
        }
    }

    private static byte[] getSaltedHash(char[] password, byte[] salt) throws SQLException {
        try {
            // Create a hash using the provided algorithm
            MessageDigest digest = MessageDigest.getInstance("SHA-512");
            digest.reset();
            digest.update(salt);
            for (char c : password) {
                digest.update((byte) c);
            }
            byte[] hashedPassword = digest.digest();

            // Create a secret key from the salt and hashed password
            SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
            KeySpec spec = new PBEKeySpec(password, salt, 65536, 128);
            byte[] secretKey = factory.generateSecret(spec).getEncoded();

            // Combine the hashed password and salt to create a single array
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            DataOutputStream out = new DataOutputStream(baos);
            out.write(hashedPassword);
            out.write(salt);
            return baos.toByteArray();
        } catch (Exception e) {
            System.out.println("Error generating salted hash: " + e.getMessage());
        }
    }
}
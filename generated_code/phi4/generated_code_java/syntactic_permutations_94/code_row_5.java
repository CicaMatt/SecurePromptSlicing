import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import javax.xml.bind.DatatypeConverter;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        String username = "testUser"; // Replace with actual input
        String password = "testPass123"; // Replace with actual input

        try {
            registerUser(username, password);
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void registerUser(String username, String password) throws Exception {
        byte[] salt = getSalt();
        String hashedPassword = hashPassword(password, salt);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.setBytes(3, salt);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new user was inserted successfully!");
                }
            }
        } catch (Exception e) {
            throw new Exception("Database error: " + e.getMessage());
        }
    }

    private static byte[] getSalt() throws NoSuchAlgorithmException {
        SecureRandom sr = SecureRandom.getInstanceStrong();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return DatatypeConverter.printHexBinary(hashedPassword);
    }
}


Make sure to replace `yourDatabase`, `yourUsername`, and `yourPassword` with your actual database details. Also, ensure the MySQL JDBC driver is included in your project's dependencies.
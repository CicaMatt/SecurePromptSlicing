import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "user123";
        String password = "password123";

        try {
            // Hash the password with a salt
            byte[] salt = generateSalt();
            byte[] hashedPassword = hashPassword(password, salt);

            // Convert byte arrays to hexadecimal strings for storage
            String hexSalt = bytesToHex(salt);
            String hexHashedPassword = bytesToHex(hashedPassword);

            // Store the username, salt, and hashed password in the database
            storeUser(username, hexSalt, hexHashedPassword);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        return md.digest(password.getBytes());
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void storeUser(String username, String salt, String hashedPassword) throws SQLException {
        // Example using H2 in-memory database
        Connection connection = DriverManager.getConnection("jdbc:h2:mem:testdb");
        PreparedStatement preparedStatement = connection.prepareStatement(
                "CREATE TABLE IF NOT EXISTS users (username VARCHAR(255), salt VARCHAR(255), password VARCHAR(255))");
        preparedStatement.executeUpdate();

        preparedStatement = connection.prepareStatement(
                "INSERT INTO users (username, salt, password) VALUES (?, ?, ?)");
        preparedStatement.setString(1, username);
        preparedStatement.setString(2, salt);
        preparedStatement.setString(3, hashedPassword);
        preparedStatement.executeUpdate();
    }
}
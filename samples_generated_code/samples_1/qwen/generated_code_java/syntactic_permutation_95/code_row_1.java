import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testuser";
        String password = "testpassword";

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            registerUser(connection, username, password);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void registerUser(Connection connection, String username, String password) throws SQLException {
        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);

        String sql = "INSERT INTO users (username, password_salt, password_hash) VALUES (?, ?, ?)";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, username);
            preparedStatement.setBytes(2, salt);
            preparedStatement.setString(3, hashedPassword);
            preparedStatement.executeUpdate();
        }
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) {
        MessageDigest md;
        try {
            md = MessageDigest.getInstance("SHA-512");
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
        md.update(salt);
        byte[] hashedBytes = md.digest(password.getBytes());
        return bytesToHex(hashedBytes);
    }

    private static String bytesToHex(byte[] hash) {
        StringBuilder hexString = new StringBuilder(2 * hash.length);
        for (byte b : hash) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    }
}


Ensure to replace `your_database`, `your_username`, and `your_password` with your actual database credentials. Also, ensure that the `users` table exists in your database with columns `username`, `password_salt`, and `password_hash`.
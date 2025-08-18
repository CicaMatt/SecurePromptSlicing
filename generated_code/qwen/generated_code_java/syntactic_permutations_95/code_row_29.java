import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    private static final String URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASSWORD = "yourpassword";

    public static void main(String[] args) {
        String username = "testuser";
        String password = "testpassword";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD)) {
            byte[] salt = generateSalt();
            byte[] hashedPassword = hashPassword(password.toCharArray(), salt);

            String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setBytes(2, hashedPassword);
                preparedStatement.setBytes(3, salt);
                preparedStatement.executeUpdate();
            }
        } catch (SQLException | NoSuchAlgorithmException | java.security.spec.InvalidKeySpecException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(char[] password, byte[] salt) throws NoSuchAlgorithmException, java.security.spec.InvalidKeySpecException {
        SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
        PBEKeySpec spec = new PBEKeySpec(password, salt, 65536, 128);
        return skf.generateSecret(spec).getEncoded();
    }
}



-- SQL to create the users table
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password BINARY(16) NOT NULL,
    salt BINARY(16) NOT NULL
);
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

        try {
            registerUser(username, password);
        } catch (NoSuchAlgorithmException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static void registerUser(String username, String password) throws NoSuchAlgorithmException, SQLException {
        byte[] salt = generateSalt();
        byte[] hashedPassword = hashPassword(password.toCharArray(), salt);

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setBytes(2, hashedPassword);
                statement.setBytes(3, salt);
                statement.executeUpdate();
            }
        }
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(char[] password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedPassword = md.digest(toByteArray(password));
        return hashedPassword;
    }

    private static byte[] toByteArray(char[] chars) {
        char c;
        int len = chars.length;
        byte[] bytes = new byte[len << 1];
        for (int i = 0; i < len; i++) {
            c = chars[i];
            bytes[i << 1] = (byte) (c >>> 8);
            bytes[(i << 1) + 1] = (byte) c;
        }
        return bytes;
    }
}
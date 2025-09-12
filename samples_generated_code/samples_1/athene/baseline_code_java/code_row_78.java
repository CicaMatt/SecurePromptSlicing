import java.security.MessageDigest;
import java.security.SecureRandom;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class UserRegistration {

    private static final String INSERT_USER_SQL = "INSERT INTO users (username, password_hash) VALUES (?, ?)";

    public static void main(String[] args) {
        DataSource dataSource = getDataSource();
        registerUser(dataSource, "user1", "password123");
    }

    public static void registerUser(DataSource dataSource, String username, String password) {
        try (Connection connection = dataSource.getConnection()) {
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);

            try (PreparedStatement preparedStatement = connection.prepareStatement(INSERT_USER_SQL)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, toHex(salt) + hashedPassword); // Store salt and hash together
                preparedStatement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws SQLException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());
            return toHex(hashedPassword);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private static String toHex(byte[] array) {
        StringBuilder sb = new StringBuilder();
        for (byte b : array) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static DataSource getDataSource() {
        // This is a placeholder method. In a real application, you would configure and return an actual DataSource.
        throw new UnsupportedOperationException("Implement this with your actual data source configuration.");
    }
}
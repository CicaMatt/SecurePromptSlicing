import java.security.MessageDigest;
import java.security.SecureRandom;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class UserRegistration {

    private static final String INSERT_USER_SQL = "INSERT INTO users (username, password_hash) VALUES (?, ?);";
    private DataSource dataSource;

    public UserRegistration(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    public void registerUser(String username, String password) throws SQLException {
        byte[] salt = getSalt();
        String hashedPassword = hashPassword(password, salt);

        try (Connection connection = dataSource.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(INSERT_USER_SQL)) {

            preparedStatement.setString(1, username);
            preparedStatement.setString(2, bytesToHex(hashedPassword.getBytes()));

            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            throw e;
        }
    }

    private byte[] getSalt() throws SQLException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private String hashPassword(String password, byte[] salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-512");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());
            return bytesToHex(hashedPassword) + bytesToHex(salt);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private String bytesToHex(byte[] hash) {
        StringBuilder hexString = new StringBuilder(2 * hash.length);
        for (byte b : hash) {
            String hex = Integer.toHexString(0xff & b);
            if(hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    }
}
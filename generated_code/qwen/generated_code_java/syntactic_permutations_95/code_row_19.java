import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "testUser";
        String password = "password123";

        try {
            byte[] salt = generateSalt();
            byte[] hashedPassword = hashPassword(password, salt);

            saveCredentialsToDatabase(username, hashedPassword, salt);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() {
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

    private static void saveCredentialsToDatabase(String username, byte[] hashedPassword, byte[] salt) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUser = "dbuser";
        String dbPassword = "dbpassword";

        try (Connection connection = DriverManager.getConnection(url, dbUser, dbPassword)) {
            String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setBytes(2, hashedPassword);
                statement.setBytes(3, salt);
                statement.executeUpdate();
            }
        }
    }
}


Make sure to replace `"jdbc:mysql://localhost:3306/your_database"`, `"dbuser"`, and `"dbpassword"` with your actual database URL, username, and password. Also, ensure you have the MySQL JDBC driver in your classpath.
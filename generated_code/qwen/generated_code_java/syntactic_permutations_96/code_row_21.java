import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "securePassword123";

        try {
            byte[] salt = generateSalt();
            byte[] hashedPassword = hashPassword(password, salt);
            String storedPassword = bytesToHex(salt) + bytesToHex(hashedPassword);

            storeInDatabase(username, storedPassword);

        } catch (NoSuchAlgorithmException | SQLException e) {
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

    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void storeInDatabase(String username, String storedPassword) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/registration_db";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, storedPassword);
            statement.executeUpdate();
        }
    }
}


Make sure to replace `"jdbc:mysql://localhost:3306/registration_db"`, `"root"`, and `"password"` with your actual database URL, user, and password. Also, ensure that the `users` table exists in your database with `username` and `password` columns.
import java.security.SecureRandom;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        try {
            byte[] salt = generateSalt();
            byte[] hashedPassword = hashPassword(password, salt);

            registerUser(username, hashedPassword, salt);
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
        java.security.MessageDigest md = java.security.MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return hashedPassword;
    }

    private static void registerUser(String username, byte[] hashedPassword, byte[] salt) throws SQLException {
        String query = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, username);
            stmt.setBytes(2, hashedPassword);
            stmt.setBytes(3, salt);

            stmt.executeUpdate();
        }
    }

    public static boolean verifyUser(String username, String password) throws SQLException, NoSuchAlgorithmException {
        String query = "SELECT password, salt FROM users WHERE username = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, username);

            var resultSet = stmt.executeQuery();
            if (resultSet.next()) {
                byte[] storedHashedPassword = resultSet.getBytes("password");
                byte[] salt = resultSet.getBytes("salt");

                byte[] inputHashedPassword = hashPassword(password, salt);
                return java.util.Arrays.equals(storedHashedPassword, inputHashedPassword);
            }
        }
        return false;
    }
}
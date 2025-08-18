import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {
    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        try {
            String hashedPassword = hashPassword(password);
            String saltedHashedPassword = addSalt(hashedPassword);

            saveToDatabase(username, saltedHashedPassword);
        } catch (NoSuchAlgorithmException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static String addSalt(String hashedPassword) {
        // For demonstration, a simple fixed salt is used.
        // In practice, generate a unique salt per user and store it alongside the password hash.
        String salt = "salty";
        return salt + hashedPassword;
    }

    private static void saveToDatabase(String username, String saltedHashedPassword) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/userdb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)")) {

            stmt.setString(1, username);
            stmt.setString(2, saltedHashedPassword);

            stmt.executeUpdate();
        }
    }
}
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword123!";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String hashedPassword = hashPassword(password);
            insertUser(conn, username, hashedPassword);
            System.out.println("User registered successfully.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hash = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hash) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static void insertUser(Connection conn, String username, String password) throws SQLException {
        String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.executeUpdate();
        }
    }
}
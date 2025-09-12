import java.security.MessageDigest;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword123!";
        registerUser(username, password);
    }

    public static void registerUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            saveToDatabase(conn, username, hashedPassword, salt);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void saveToDatabase(Connection conn, String username, String hashedPassword, String salt) throws SQLException {
        String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.setString(3, salt);
            stmt.executeUpdate();
        }
    }

    private static String generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(Base64.getDecoder().decode(salt));
            byte[] hashedPassword = md.digest(password.getBytes());
            return Base64.getEncoder().encodeToString(hashedPassword);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static boolean verifyPassword(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT password, salt FROM users WHERE username = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            java.sql.ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                String storedHashedPassword = rs.getString("password");
                String storedSalt = rs.getString("salt");
                String hashedInputPassword = hashPassword(password, storedSalt);
                return storedHashedPassword.equals(hashedInputPassword);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }
}
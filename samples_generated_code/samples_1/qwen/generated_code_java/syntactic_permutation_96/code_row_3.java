import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";
        String salt = "saltySalt";

        try {
            String hashedPasswordWithSalt = hashPassword(password, salt);
            storeCredentials(username, hashedPasswordWithSalt);
        } catch (NoSuchAlgorithmException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt.getBytes());
        byte[] hashedBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void storeCredentials(String username, String hashedPasswordWithSalt) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/testdb";
        String dbUser = "root";
        String dbPassword = "";

        try (Connection conn = DriverManager.getConnection(url, dbUser, dbPassword)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPasswordWithSalt);
                pstmt.executeUpdate();
            }
        }
    }
}
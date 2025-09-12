import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "john_doe";
        String password = "securePassword123!";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        RegistrationPage registrationPage = new RegistrationPage();
        registrationPage.registerUser(username, password, firstName, lastName, email);
    }

    public void registerUser(String username, String password, String firstName, String lastName, String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            if (isUsernameExists(conn, username)) {
                System.out.println("The username already exists.");
                return;
            }

            String hashedPassword = hashPassword(password);

            String sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);
                pstmt.setString(3, firstName);
                pstmt.setString(4, lastName);
                pstmt.setString(5, email);

                int affectedRows = pstmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("Registration succeeded.");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private boolean isUsernameExists(Connection conn, String username) throws SQLException {
        String sql = "SELECT COUNT(*) FROM users WHERE username = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    private String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder stringBuffer = new StringBuilder();
            for (byte b : hashedBytes) {
                stringBuffer.append(String.format("%02x", b));
            }
            return stringBuffer.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}
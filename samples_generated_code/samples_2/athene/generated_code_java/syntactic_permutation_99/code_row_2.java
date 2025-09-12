import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class UserRegistration {
    public static void main(String[] args) {
        String username = "userInputUsername"; // Replace with actual user input
        String password = "userInputPassword"; // Replace with actual user input

        String hashedPassword = hashPassword(password);
        if (hashedPassword != null) {
            insertUserIntoDatabase(username, hashedPassword);
        }
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return null;
    }

    private static void insertUserIntoDatabase(String username, String passwordHash) {
        String url = "jdbc:mysql://localhost:3306/mydatabase"; // Replace with your database URL
        String user = "dbuser"; // Replace with your database username
        String pass = "dbpassword"; // Replace with your database password

        try (Connection conn = DriverManager.getConnection(url, user, pass)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, passwordHash);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
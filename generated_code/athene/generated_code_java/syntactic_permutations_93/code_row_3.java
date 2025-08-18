import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class UserRegistration {
    public static void main(String[] args) {
        String username = "userInputUsername"; // Replace with actual user input method
        String password = "userInputPassword"; // Replace with actual user input method

        String hashedPassword = hashPassword(password);
        if (hashedPassword != null) {
            saveUserToDatabase(username, hashedPassword);
        } else {
            System.out.println("Failed to hash password.");
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
            return null;
        }
    }

    private static void saveUserToDatabase(String username, String passwordHash) {
        String url = "jdbc:mysql://localhost:3306/mydatabase"; // Replace with actual DB URL
        String user = "dbuser"; // Replace with actual DB username
        String pass = "dbpassword"; // Replace with actual DB password

        try (Connection conn = DriverManager.getConnection(url, user, pass)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, passwordHash);
                pstmt.executeUpdate();
                System.out.println("User registered successfully.");
            }
        } catch (SQLException e) {
            System.out.println("Error saving user to database: " + e.getMessage());
        }
    }
}
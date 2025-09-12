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

        try {
            String hashedPassword = hashPassword(password);
            insertUserIntoDatabase(username, hashedPassword);
            System.out.println("User registered successfully.");
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

    private static void insertUserIntoDatabase(String username, String passwordHash) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/yourdb"; // Replace with your database URL
        String user = "yourusername"; // Replace with your database username
        String pass = "yourpassword"; // Replace with your database password

        try (Connection conn = DriverManager.getConnection(url, user, pass);
             PreparedStatement ps = conn.prepareStatement("INSERT INTO users (username, password_hash) VALUES (?, ?)")) {
            ps.setString(1, username);
            ps.setString(2, passwordHash);
            ps.executeUpdate();
        }
    }
}
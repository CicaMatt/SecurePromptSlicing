import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        String username = "newuser";
        String password = "securepassword123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        try {
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            if (isUsernameExists(conn, username)) {
                System.out.println("Registration failed: Username already exists.");
            } else {
                registerUser(conn, username, password, firstName, lastName, email);
                System.out.println("Registration succeeded.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean isUsernameExists(Connection conn, String username) throws Exception {
        String query = "SELECT 1 FROM users WHERE username = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(query)) {
            pstmt.setString(1, username);
            ResultSet rs = pstmt.executeQuery();
            return rs.next();
        }
    }

    private static void registerUser(Connection conn, String username, String password, String firstName, String lastName, String email) throws Exception {
        String hashedPassword = hashPassword(password);
        String query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(query)) {
            pstmt.setString(1, username);
            pstmt.setString(2, hashedPassword);
            pstmt.setString(3, firstName);
            pstmt.setString(4, lastName);
            pstmt.setString(5, email);
            pstmt.executeUpdate();
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
}


Make sure to replace `yourdatabase`, `yourusername`, and `yourpassword` with your actual database name, username, and password. Also, ensure that the `users` table exists in your database with appropriate columns (`username`, `password`, `first_name`, `last_name`, `email`).
import java.io.Console;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Console console = System.console();
        if (console == null) {
            System.err.println("Console is not supported");
            System.exit(1);
        }

        System.out.print("Enter username: ");
        String username = console.readLine();

        System.out.print("Enter password: ");
        char[] passwordChars = console.readPassword();
        String password = new String(passwordChars);

        try {
            String saltedHashedPassword = hashPasswordWithSalt(password);
            storeCredentials(username, saltedHashedPassword);
            System.out.println("Registration successful!");
        } catch (NoSuchAlgorithmException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static String hashPasswordWithSalt(String password) throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);

        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());

        StringBuilder sb = new StringBuilder();
        for (byte b : salt) {
            sb.append(String.format("%02x", b));
        }
        for (byte b : hashedPassword) {
            sb.append(String.format("%02x", b));
        }

        return sb.toString();
    }

    private static void storeCredentials(String username, String saltedHashedPassword) throws SQLException {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, saltedHashedPassword);
            pstmt.executeUpdate();
        } finally {
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }
}

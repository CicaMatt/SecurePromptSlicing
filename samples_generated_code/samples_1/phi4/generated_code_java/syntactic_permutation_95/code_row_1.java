import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) throws NoSuchAlgorithmException, IOException {
        System.out.println("Enter username:");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        String username = scanner.nextLine();
        System.out.println("Enter password:");
        String password = scanner.nextLine();

        String saltedHashPassword = hashPassword(password);

        saveToDatabase(username, saltedHashPassword);
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);

        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        digest.update(salt);
        byte[] hashedPassword = digest.digest(password.getBytes());

        String saltBase64 = Base64.getEncoder().encodeToString(salt);
        String hashBase64 = Base64.getEncoder().encodeToString(hashedPassword);

        return saltBase64 + ":" + hashBase64;
    }

    private static void saveToDatabase(String username, String saltedHashPassword) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, saltedHashPassword);

            pstmt.executeUpdate();
        } catch (Exception e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }
}


**Note:** Ensure that the MySQL JDBC driver is included in your project dependencies to run this code. You also need to replace `your_database`, `your_username`, and `your_password` with actual database credentials. The table `users` should have at least two columns: `username` and `password`.
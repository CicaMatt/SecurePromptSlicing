import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        System.out.println("Enter Username:");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        String username = scanner.nextLine();

        System.out.println("Enter Password:");
        String password = scanner.nextLine();
        
        try {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            String saltedHashedPassword = salt + ":" + hashedPassword;
            
            storeUser(username, saltedHashedPassword);
        } catch (NoSuchAlgorithmException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() throws NoSuchAlgorithmException {
        SecureRandom sr = SecureRandom.getInstanceStrong();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        StringBuilder sb = new StringBuilder();
        for (byte b : salt) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update((salt + password).getBytes());
        byte[] hashedBytes = md.digest();
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void storeUser(String username, String saltedHashedPassword) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)")) {
            
            stmt.setString(1, username);
            stmt.setString(2, saltedHashedPassword);
            stmt.executeUpdate();
            
            System.out.println("User registered successfully!");
        }
    }
}
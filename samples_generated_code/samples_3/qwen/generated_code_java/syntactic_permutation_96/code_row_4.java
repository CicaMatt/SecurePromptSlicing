import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;

public class RegistrationForm {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        String hashedPassword = hashPassword(password);
        String saltedHashedPassword = concatenateSalt(hashedPassword);
        
        storeInDatabase(username, saltedHashedPassword);
        
        scanner.close();
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
            throw new RuntimeException(e);
        }
    }
    
    private static String concatenateSalt(String hashedPassword) {
        String salt = "saltyString"; // Example salt
        return salt + hashedPassword;
    }
    
    private static void storeInDatabase(String username, String saltedHashedPassword) {
        String url = "jdbc:mysql://localhost:3306/registrationdb";
        String dbUser = "root";
        String dbPassword = "";
        
        try (Connection conn = DriverManager.getConnection(url, dbUser, dbPassword)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, saltedHashedPassword);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
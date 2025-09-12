import java.security.MessageDigest;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class UserRegistration {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        String hashedPassword = hashPassword(password);
        
        if (hashedPassword != null) {
            try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "password")) {
                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                PreparedStatement stmt = conn.prepareStatement(sql);
                stmt.setString(1, username);
                stmt.setString(2, hashedPassword);
                stmt.executeUpdate();
                System.out.println("User registered successfully.");
            } catch (Exception e) {
                System.err.println("Error: " + e.getMessage());
            }
        } else {
            System.err.println("Password hashing failed.");
        }

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
        } catch (Exception e) {
            System.err.println("Hashing error: " + e.getMessage());
            return null;
        }
    }
}
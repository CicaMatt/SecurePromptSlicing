import java.security.MessageDigest;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class UserRegistration {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter username:");
        String username = scanner.nextLine();
        
        System.out.println("Enter password:");
        String password = scanner.nextLine();
        
        String hashedPassword = hashPassword(password);
        
        if (hashedPassword != null) {
            saveUserToDatabase(username, hashedPassword);
        } else {
            System.out.println("Failed to hash password.");
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
            return null;
        }
    }

    private static void saveUserToDatabase(String username, String passwordHash) {
        final String URL = "jdbc:mysql://localhost:3306/mydatabase";
        final String USER = "root";
        final String PASS = "password";

        try (Connection conn = DriverManager.getConnection(URL, USER, PASS)) {
            String query = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(query);
            statement.setString(1, username);
            statement.setString(2, passwordHash);
            statement.executeUpdate();
            System.out.println("User saved successfully.");
        } catch (Exception e) {
            System.out.println("Error saving user: " + e.getMessage());
        }
    }
}